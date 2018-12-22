#ifndef _DASH
#define _DASH

#include "Sort.h"

/**
* \author {DEVILLERS Alexandre, KRIMI Imran}
* \brief Class hérité de sort, permet de créé et gerer un sort dash.
*/
class Dash final: public Sort {
public:

    /**
    * \brief Constructeur par défaut
    */
    Dash();


    /**
    * \brief Actualise l'entite passé en paramètre en fontion de l'entite
    */
    void actualiseEntite(Entite & e);

    /**
    * \brief Lance le dash depuis pos à cible
    */
    bool lance(const complex<float> & pos, complex<float> cible);

    /**
    * \brief Effectue les actions une fois que le sort à touché avec la 'i'eme entite (gestion des entites/récupération)
    */
    void aTouche(const unsigned int i);

    /**
    * \brief Permet d'obtenir l'id de la class fille
    */
    const int getId() const;

private:



};

#endif
