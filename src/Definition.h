#ifndef _DEFINITION
#define _DEFINITION

#include <chrono>

/**
* \brief Donne la taille en X des pixel de la fenetre (pas l'affichage juste la fenetre théorique)
*/
const int DIMX();
/**
* \brief Donne la taille en Y des pixel de la fenetre (pas l'affichage juste la fenetre théorique)
*/
const int DIMY();
/**
* \brief Donne la taille d'une tuile, elle sert d'unité de mesure pour que si on change la taille ici la physique soit la même
*/
const int TBLOCK();

/**
* \brief Permet de set le temps du début du programme
*/
const auto START = std::chrono::high_resolution_clock::now();

/**
* \brief Donne le temps actuel en comparant le temps actuel et START
*/
const float tempsEcoule();

#endif
