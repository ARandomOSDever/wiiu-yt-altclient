#include <coreinit/memory.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_rwops.h>
#include <string>
#include <map>
#include "exceptions.h"

class Font {
private:
    std::map<int, TTF_Font *> fonts; // Used to be able to have multiple font sizes
    SDL_Renderer *renderer;
    SDL_RWops *ttfData;
public:
    Font(SDL_Renderer *renderer);
    ~Font();
    FontError reinitFontsWithFile(std::string fontPath);
};

Font::Font(SDL_Renderer *r) {
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s", SDL_GetError());
        TTF_Quit();
        throw FONT_INIT_SDLTTF_FAILED;
    }
    reinitFontsWithFile("sys");
    renderer = r;
}

Font::~Font() {

}

FontError Font::reinitFontsWithFile(std::string fontPath = "sys") {
    if (fontPath != "sys"){
        ttfData = SDL_RWFromFile(fontPath.c_str(), "rb");
    }
    else {
        void *ttfPtr;
        uint32_t ttfSize;
        OSGetSharedData(OS_SHAREDDATATYPE_FONT_STANDARD, 0, &ttfPtr, &ttfSize);
        ttfData = SDL_RWFromConstMem(&ttfPtr, (int)ttfSize);
    }
    if (fonts.size() == 0){
        fonts[24] = TTF_OpenFontRW(ttfData, 0, 24);
    }
    else {
        for (auto const& [size, fontptr] : fonts){
            TTF_CloseFont(fontptr);
            fonts[size] = TTF_OpenFontRW(ttfData, 0, size);
        }
    }
    return FONT_OK;
}