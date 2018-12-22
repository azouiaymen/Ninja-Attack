#ifndef _TORTUE
#define _TORTUE

#include "Personnage.h"
using namespace std;

/**
* \author {DEVILLERS Alexandre, AZOUI Aymen}
* \brief Class h�rit� de personnage, permet de cr�� et gerer une tortue.
*/
class Tortue final: public Personnage {
public:

    /**
    * \brief Constructeur par d�faut
    */
    Tortue();
    /**
    * \brief Constructeur avec une zone de spawn d�finie
    */
    Tortue(const complex<float> & pos);
    /**
    * \brief Destructeur
    */
    ~Tortue();


    /**
    * \brief Permet de r�cuperer le pointeur du sort Contact, ATTENTION A MANIPULER AVEC PRECAUTION CAR EXISTE UNE VERSION POINTEUR NON CONST
    */
    const Contact * getContact() const;
    /**
    * \brief Permet de r�cuperer le pointeur du sort Contact, ATTENTION A MANIPULER AVEC PRECAUTION CAR POINTEUR NON CONST
    */
    Contact * getContact();
    /**
    * \brief Permet de d�finir le Contact depuis un autre pointeur de Contact
    */
    void setContact(const Contact * s);


    /**
    * \brief Lance contact
    */
    void lanceContact();
    /**
    * \brief Actuatlise contact en fonction de entite
    */
    void actualiseEntiteContact();


    /**
    * \brief L'IA de la tortue, qui a en entr�e l'entit�e du personnage enemis (le hero), et la carte
    */
    void reflechis(const Entite & hero, const Carte & carte);


    /**
    * \brief Permet de faire sauter la tortue
    */
    void saute();
    /**
    * \brief Permet de d�placer la tortue sur la droite
    */
    void droite();
    /**
    * \brief Permet de d�placer la tortue sur la gauche
    */
    void gauche();

    /**
    * \brief Permet d'obtenir dans un vector de pointeur de sort les sorts de la tortue, ATTENTION A MANIPULER AVEC PRECAUTION CAR VECTOR DE POINTEURS
    */
    vector<Sort*> getSort();
    /**
    * \brief Permet d'obtenir l'id (un entier unique pour chaque class h�rit�es) de cette classe fille
    */
    const int getId() const;

private:

    Contact *contact; //!< \brief Sort de la tortue (Contact)

};

#endif
