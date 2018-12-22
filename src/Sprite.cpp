#include "Sprite.h"

void Sprite::init(SDL_Renderer * r, string i, int n, int f) {
    tChange = tempsEcoule();
    it = 0;
    rendu = r;
    image = IMG_LoadTexture(rendu, i.c_str());
    SDL_QueryTexture(image, NULL, NULL, &cible.w, &cible.h);
    cible.w/=n;
    cible.x = 0;
    cible.y = 0;
    itMax = n;
    fps = f;
    dest.x = dest.y = dest.w = dest.h = 0;
}


void Sprite::afficher(complex<float> pos, complex<float> taille, bool miroir, float angle) {
    if(taille.real() < 0) {
        pos.real(pos.real()+taille.real());
        taille.real(taille.real() * (-1));
    }
    if(taille.imag() < 0) {
        pos.imag(pos.imag()+taille.imag());
        taille.imag(taille.imag() * (-1));
    }
    dest.x = pos.real();
    dest.y = pos.imag();
    dest.w = taille.real();
    dest.h = taille.imag();
    SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
    if(miroir) {
        flip = SDL_FLIP_VERTICAL;
    } else {
        flip = SDL_FLIP_NONE;
    }
    SDL_RenderCopyEx(rendu, image, &cible, &dest, angle, NULL, flip);
    testChangeIt();
}

void Sprite::afficher(float posX, float posY, float tailleX, float tailleY, bool miroir, float angle) {
    if(tailleX < 0) {
        posX+=tailleX;
        tailleX*=(-1);
    }
    if(tailleY < 0) {
        posY+=tailleY;
        tailleY*=(-1);
    }
    dest.x = posX;
    dest.y = posY;
    dest.w = tailleX;
    dest.h = tailleY;
    SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
    if(miroir) {
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        flip = SDL_FLIP_NONE;
    }
    SDL_RenderCopyEx(rendu, image, &cible, &dest, angle, NULL, flip);
    testChangeIt();
}




void Sprite::testChangeIt() {
    int time = tempsEcoule();
    if((time - tChange) > (1000/fps)) {
        it++;
        tChange = time;
        it = it%itMax;
        cible.x = cible.w * it;
    }
}
