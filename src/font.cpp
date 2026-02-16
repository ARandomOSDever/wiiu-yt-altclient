#include "font.h"

FontSys::FontSys(SDL_Renderer *r) {
    if (TTF_Init() == -1) {
        TTF_Quit();
        throw FONTSYS_INIT_SDLTTF_FAILED;
    }
    reinitFontsWithFile("sys");
    renderer = r;
}

FontSys::~FontSys() {
    for (auto const& [size, fontptr] : fonts){
            TTF_CloseFont(fontptr);
            fonts.erase(size);
        }
    SDL_RWclose(ttfData);
}

void FontSys::ensureFontIsLoaded(int size) {
    if (!fonts[size]) {
        fonts[size] = TTF_OpenFontRW(ttfData, 0, size);
    }
}

FontError FontSys::reinitFontsWithFile(std::string fontPath = "sys") {
    if (fontPath == "sys"){
        void *ttfPtr = nullptr;
        uint32_t ttfSize = 0;
        OSGetSharedData(OS_SHAREDDATATYPE_FONT_STANDARD, 0, &ttfPtr, &ttfSize); 
        ttfData = SDL_RWFromConstMem(ttfPtr, (int)ttfSize);
    }
    else {
       ttfData = SDL_RWFromFile(fontPath.c_str(), "rb"); 
    }
    fonts[24] = TTF_OpenFontRW(ttfData, 0, 24);
    
    for (auto const& [size, fontptr] : fonts){
        TTF_CloseFont(fontptr);
        fonts[size] = TTF_OpenFontRW(ttfData, 0, size);
    }
    return FONTSYS_OK;
}

SDL_Rect FontSys::textBounds(const char* text, int size) {
    SDL_Rect out;
    ensureFontIsLoaded(size);
    TTF_SizeUTF8(fonts[size], text, &out.w, &out.h);
    return out;
}

FontError FontSys::drawText(int x, int y, const char* text, int size, SDL_Color fgColor, int wrapLength=0) {
    ensureFontIsLoaded(size);
    SDL_Surface *surf;
    if (strlen(text) == 0) return FONTSYS_OK; // RenderUTF8 returns error when strlen == 0
    surf = TTF_RenderUTF8_Blended_Wrapped(fonts[size], text, fgColor, wrapLength);
    if (surf == nullptr) {
        return FONTSYS_RENDERTEXT_FAILED;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == nullptr) return FONTSYS_SURF2TEXT_FAILED;
    SDL_Rect textRect = textBounds(text, size);
    textRect.x = x;
    textRect.y = y;
    int res = SDL_RenderCopy(renderer, texture, nullptr, &textRect);
    if (res < 0) return FONTSYS_RENDERCOPY_FAILED;
    return FONTSYS_OK;
}