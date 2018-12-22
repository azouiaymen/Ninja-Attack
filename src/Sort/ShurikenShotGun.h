#ifndef _SHURIKENSHOTGUN
#define _SHURIKENSHOTGUN

#include "Sort.h"

/**
* \author {DEVILLERS Alexandre, KRIMI Imran}
* \brief Class h�rit� de sort, permet de cr�� et gerer un sort shuriken shot gun.
*/
class ShurikenShotGun final: public Sort {
public:

    /**
    * \brief Constructeur par d�faut
    */
    ShurikenShotGun();


    /**
    * \brief Lance le sort depuis pos � cible
    */
    bool lance(const complex<float> & pos, complex<float> cible);

    /**
    * \brief Permet d'obtenir l'id de la class fille
    */
    const int getId() const;

private:

    /**
    * \brief Actualise la hitbox de la 'e'eme entite de entites
    */
    void actualiseHitbox(const unsigned int e);

    /**
    * \brief Gere la colision avec un mur sur l'axe X de la 'e'eme entite sur la tuile i,j de carte
    */
    void colisionMurX(const unsigned int e, const int i, const int j, const Carte & carte);
    /**
    * \brief Gere la colision avec un mur sur l'axe Y de la 'e'eme entite sur la tuile i,j de carte
    */
    void colisionMurY(const unsigned int e, const int i, const int j, const Carte & carte);

};

#endif
