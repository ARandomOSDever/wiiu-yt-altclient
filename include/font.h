#pragma once
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rwops.h>
#include "ytACl_exceptions.h"
#include <SDL2/SDL_ttf.h>
#include <coreinit/memory.h>
#include <string>
class FontSys {
private:
    std::map<int, TTF_Font *> fonts; // Used to be able to have multiple font sizes
    SDL_Renderer *renderer;
    SDL_RWops *ttfData;
public:
    FontSys(SDL_Renderer *renderer);
    ~FontSys();
    FontError reinitFontsWithFile(std::string fontPath);
    SDL_Rect textBounds(const char* text, int size);
    void ensureFontIsLoaded(int size);
    FontError drawText(int x, int y, const char* text, int size, SDL_Color fgColor, int wrapLength);
};