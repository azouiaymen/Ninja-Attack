#ifndef _HERO
#define _HERO

#include "Personnage.h"
using namespace std;

/**
* \author {DEVILLERS Alexandre, AZOUI Aymen}
* \brief Class h�rit� de personnage, permet de cr�� et gerer un hero.
*/
class Hero final: public Personnage {
public:

    /**
    * \brief Constructeur par d�faut.
    */
    Hero();
    /**
    * \brief Constructeur avec une zone de spawn.
    */
    Hero(const complex<float> & spawn);
    /**
    * \brief Destructeur
    */
    ~Hero();


    /**
    * \brief Lance le sort shuriken trois coup sur la cible
    */
    void lanceShurikenTroisCoups(complex<float> cible = complex<float>(0,0));
    /**
    * \brief Actualise le sort shuriken trois coup sur la cible (Obligatoire car sort asyncrone)
    */
    void actualiseEntiteShurikenTroisCoups(complex<float> cible = complex<float>(0,0));

    /**
    * \brief Permet de r�cuperer le pointeur du sort ShurikenTroisCoups, ATTENTION A MANIPULER AVEC PRECAUTION CAR EXISTE UNE VERSION POINTEUR NON CONST
    */
    const ShurikenTroisCoups * getShurikenTroisCoups() const;
    /**
    * \brief Permet de r�cuperer le pointeur du sort ShurikenTroisCoups, , ATTENTION A MANIPULER AVEC PRECAUTION CAR POINTEUR NON CONST
    */
    ShurikenTroisCoups * getShurikenTroisCoups();
    /**
    * \brief Permet de d�finir le ShurikenTroisCoups depuis un autre pointeur de ShurikenTroisCoups
    */
    void setShurikenTroisCoups(const ShurikenTroisCoups * s);


    /**
    * \brief Lance le sort shuriken shot gun sur la cible
    */
    void lanceShurikenShotGun(complex<float> cible = complex<float>(0,0));

    /**
    * \brief Permet de r�cuperer le pointeur du sort ShurikenShotGun, ATTENTION A MANIPULER AVEC PRECAUTION CAR EXISTE UNE VERSION POINTEUR NON CONST
    */
    const ShurikenShotGun * getShurikenShotGun() const;
    /**
    * \brief Permet de r�cuperer le pointeur du sort ShurikenShotGun, , ATTENTION A MANIPULER AVEC PRECAUTION CAR POINTEUR NON CONST
    */
    ShurikenShotGun * getShurikenShotGun();
    /**
    * \brief Permet de d�finir le ShurikenShotGun depuis un autre pointeur de ShurikenShotGun
    */
    void setShurikenShotGun(const ShurikenShotGun * s);


    /**
    * \brief Lance le sort dash sur la cible
    */
    void lanceDashHero(complex<float> cible = complex<float>(0,0));
    /**
    * \brief Actualise l'entite du hero pour suivre le dash
    */
    void actualiseEntiteDashHero();


    /**
    * \brief Permet de r�cuperer le pointeur du sort DashHero, ATTENTION A MANIPULER AVEC PRECAUTION CAR EXISTE UNE VERSION POINTEUR NON CONST
    */
    const DashHero * getDashHero() const;
    /**
    * \brief Permet de r�cuperer le pointeur du sort DashHero, ATTENTION A MANIPULER AVEC PRECAUTION CAR POINTEUR NON CONST
    */
    DashHero * getDashHero();
    /**
    * \brief Permet de d�finir le DashHero depuis un autre pointeur de DashHero
    */
    void setDashHero(const DashHero * s);

    /**
    * \brief Permet d'obtenir dans un vector de pointeur de sort les sorts du hero, ATTENTION A MANIPULER AVEC PRECAUTION CAR VECTOR DE POINTEURS
    */
    vector<Sort*> getSort();
    /**
    * \brief Permet d'obtenir l'id (un entier unique pour chaque class h�rit�es) de cette classe fille
    */
    const int getId() const;

    /**
    * \brief Fait sauter le hero
    */
    void saute();
    /**
    * \brief Fait aller � droite le hero
    */
    void droite();
    /**
    * \brief Fait aller � gauche le hero
    */
    void gauche();
    /**
    * \brief Immobilise le hero
    */
    void attend();

    /**
    * \brief Effectue les actions li� � la mort du hero (le reinitialise)
    */
    void meurt();

private:

    ShurikenTroisCoups *shurikenTroisCoups; //!< \brief Un des sorts du hero (Lance 3 shuriken en asyncrone)
    ShurikenShotGun *shurikenShotGun; //!< \brief Un des sorts du hero (Lance 3 shuriken en syncrone avec des angles diff�rents)
    DashHero *dashHero; //!< \brief Un des sorts du hero (D�placement rapide sur une courte distance)

};

#endif
