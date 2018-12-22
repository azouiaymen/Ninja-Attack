#ifndef _SPRITE
#define _SPRITE

#include "Definition.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <complex>
using namespace std;

/**
* \author {DEVILLERS Alexandre}
* \brief Petite class bien pratique pour afficher les animations.
*/

class Sprite {
public:

    /**
    * \brief Initialise le sprite en fonction des paramètres choisis.
    * @param r le renderer utilisé (SDL2)
    * @param i le path de l'image (qui doit être en ligne)
    * @param n le nombre d'image de l'animation
    * @param f le nombres d'images à afficher par seconde
    */
    void init(SDL_Renderer * r, string i, int n, int f);

    /**
    * \brief Affiche le sprite.
    * @param pos la position où le sprite sera affiché
    * @param taille la taille que prendra le sprite
    * @param miroir true pour inverser le sprite (false de base)
    * @param angle angle en degres pour tourner le sprite (0 de base)
    */
    void afficher(complex<float> pos, complex<float> taille, bool miroir = false, float angle = 0);

    /**
    * \brief Affiche le sprite.
    * @param posX,posY la position où le sprite sera affiché
    * @param taille la taille que prendra le sprite
    * @param miroir true pour inverser le sprite (false de base)
    * @param angle angle en degres pour tourner le sprite (0 de base)
    */
    void afficher(float posX, float posY, float tailleX, float tailleY, bool miroir = false, float angle = 0);

private:

    int it; //!< \brief Itérateur actuel dans l'animation
    int itMax; //!< \brief Nombre max d'image de l'animation
    int fps; //!< \brief Image par seconde
    int tChange; //!< \brief Temps du dernier changement d'image dans l'animation
    SDL_Rect cible; //!< \brief Rectangle cible sur l'image
    SDL_Rect dest; //!< \brief Rectangle de destination sur le renderer
    SDL_Texture * image; //!< \brief L'image
    SDL_Renderer * rendu; //!< \brief Le renderer

    void testChangeIt(); //!< \brief Check si l'animation doit changer de frame, si oui, alors le changement est effectué

};

#endif
