#include <SDL2/SDL.h>
#include "DefinitionSDL.h"
#include "Definition.h"
#include <iostream>
using namespace std;

const int AFFDIMX() {
    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);
    if(dm.w >= 1024)
        return dm.w;
    return 1024;
}

const int AFFDIMY() {
    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);
    if(dm.h >= 768)
        return dm.h;
    return 768;
}

const float AFFCOEF() {
    return ((float)AFFDIMX()/(float)DIMX());
}
