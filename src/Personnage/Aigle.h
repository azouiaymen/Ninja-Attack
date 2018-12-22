#ifndef _AIGLE
#define _AIGLE

#include "Personnage.h"
using namespace std;

/**
* \author {DEVILLERS Alexandre, AZOUI Aymen}
* \brief Class hérité de personnage, permet de créé et gerer un aigle.
*/
class Aigle final: public Personnage {
public:

    /**
    * \brief Constructeur par défaut
    */
    Aigle();
    /**
    * \brief Constructeur avec une zone de spawn définie
    */
    Aigle(const complex<float> & pos);
    /**
    * \brief Destructeur
    */
    ~Aigle();


    /**
    * \brief Lance un tir sur la cible
    */
    void lanceTir(complex<float> cible);

    /**
    * \brief Permet de récuperer le pointeur du sort Tir, ATTENTION A MANIPULER AVEC PRECAUTION CAR EXISTE UNE VERSION POINTEUR NON CONST
    */
    const Tir * getTir() const;
    /**
    * \brief Permet de récuperer le pointeur du sort Tir, ATTENTION A MANIPULER AVEC PRECAUTION CAR POINTEUR NON CONST
    */
    Tir * getTir();
    /**
    * \brief Permet de définir le Tir depuis un autre pointeur de Tir
    */
    void setTir(const Tir * s);


    /**
    * \brief L'IA de l'aigle, qui a en entrée l'entitée du personnage enemis (le hero), et la carte
    */
    void reflechis(const Entite & hero, const Carte & carte);


    /**
    * \brief Permet de faire sauter l'aigle
    */
    void saute();
    /**
    * \brief Permet de déplacer l'aigle sur la droite
    */
    void droite();
    /**
    * \brief Permet de déplacer l'aigle sur la gauche
    */
    void gauche();

    /**
    * \brief Permet d'obtenir dans un vector de pointeur de sort les sorts de l'aigle, ATTENTION A MANIPULER AVEC PRECAUTION CAR VECTOR DE POINTEURS
    */
    vector<Sort*> getSort();
    /**
    * \brief Permet d'obtenir l'id (un entier unique pour chaque class héritées) de cette classe fille
    */
    const int getId() const;

private:

    Tir *tir; //!< \brief Sort de l'aigle (Tir)

};

#endif
