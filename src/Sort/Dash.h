#ifndef _DASH
#define _DASH

#include "Sort.h"

/**
* \author {DEVILLERS Alexandre, KRIMI Imran}
* \brief Class h�rit� de sort, permet de cr�� et gerer un sort dash.
*/
class Dash final: public Sort {
public:

    /**
    * \brief Constructeur par d�faut
    */
    Dash();


    /**
    * \brief Actualise l'entite pass� en param�tre en fontion de l'entite
    */
    void actualiseEntite(Entite & e);

    /**
    * \brief Lance le dash depuis pos � cible
    */
    bool lance(const complex<float> & pos, complex<float> cible);

    /**
    * \brief Effectue les actions une fois que le sort � touch� avec la 'i'eme entite (gestion des entites/r�cup�ration)
    */
    void aTouche(const unsigned int i);

    /**
    * \brief Permet d'obtenir l'id de la class fille
    */
    const int getId() const;

private:



};

#endif
