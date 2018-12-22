#ifndef _HITBOX
#define _HITBOX

#include "Definition.h"
#include <complex>
using namespace std;

/**
* \author {DEVILLERS Alexandre}
* \brief Petite class bien pratique pour gerer les colisions de hitbox.
*/

class Hitbox {
public:

    /**
    * \brief Constructeur par defaut
    */
    Hitbox();
    /**
    * \brief Constructeur avec initialisation de tout les paramètres passé en arguments
    * @param p pour pos
    * @param ta pour taille
    * @param ty pour type
    */
    Hitbox(const complex<float> p, const complex<float> ta, const int ty);


    /**
    * \brief Accesseur de type
    */
    const int getType() const;
    /**
    * \brief Mutateur de type
    */
    void setType(const int type);

    /**
    * \brief Accesseur de pos, ATTENTION IL EXISTE UNE VERSION NON CONST PAR REFERENCE
    */
    const complex<float> & getPos() const;
    /**
    * \brief Accesseur de pos, ATTENTION VERSION NON CONST PAR REFERENCE
    */
    complex<float> & getPos();
    /**
    * \brief Mutateur de pos
    */
    void setPos(const complex<float> &cplx);

    /**
    * \brief Accesseur de taille, ATTENTION IL EXISTE UNE VERSION NON CONST PAR REFERENCE
    */
    const complex<float> & getTaille() const;
    /**
    * \brief Accesseur de taille, ATTENTION VERSION NON CONST PAR REFERENCE
    */
    complex<float> & getTaille();
    /**
    * \brief Mutateur de taille
    */
    void setTaille(const complex<float> &cplx);


    /**
    * \brief Mutateur de taille
    */
    bool touche(const Hitbox & hitb) const;

private:

    int type; //!< \brief Type de hitbox, 0 on passe dedant, 1 c'est un mur, 2 un liquide
    complex<float> pos; //!< \brief Position de la hitbox
    complex<float> taille; //!< \brief Taille de la hitbox

};

#endif
