#ifndef _REQUIN
#define _REQUIN

#include "Personnage.h"
using namespace std;

/**
* \author {DEVILLERS Alexandre, AZOUI Aymen}
* \brief Class h�rit� de personnage, permet de cr�� et gerer un requin.
*/
class Requin final: public Personnage {
public:

    /**
    * \brief Constructeur par d�faut
    */
    Requin();
    /**
    * \brief Constructeur avec une zone de spawn d�finie
    */
    Requin(const complex<float> & pos);
    /**
    * \brief Destructeur
    */
    ~Requin();

    /**
    * \brief Lance un dash sur la cible
    */
    void lanceDash(complex<float> cible);
    /**
    * \brief Actualise l'entite du requin selon le dash
    */
    void actualiseEntiteDash();

    /**
    * \brief Permet de r�cuperer le pointeur du sort Dash, ATTENTION A MANIPULER AVEC PRECAUTION CAR EXISTE UNE VERSION POINTEUR NON CONST
    */
    const Dash * getDash() const;
    /**
    * \brief Permet de r�cuperer le pointeur du sort Dash, ATTENTION A MANIPULER AVEC PRECAUTION CAR POINTEUR NON CONST
    */
    Dash * getDash();
    /**
    * \brief Permet de d�finir le Dash depuis un autre pointeur de Dash
    */
    void setDash(const Dash * s);

    /**
    * \brief L'IA de l'aigle, qui a en entr�e l'entit�e du personnage enemis (le hero), et la carte
    */
    void reflechis(const Entite & hero, const Carte & carte);

    /**
    * \brief Permet de d�placer le requin sur la droite
    */
    void droite();
    /**
    * \brief Permet de d�placer le requin sur la gauche
    */
    void gauche();


    /**
    * \brief Permet d'obtenir dans un vector de pointeur de sort les sorts du requin, ATTENTION A MANIPULER AVEC PRECAUTION CAR VECTOR DE POINTEURS
    */
    vector<Sort*> getSort();

    /**
    * \brief Permet d'obtenir l'id (un entier unique pour chaque class h�rit�es) de cette classe fille
    */
    const int getId() const;

private:

    Dash *dash; //!< \brief Sort du requin (Dash)

};


#endif
