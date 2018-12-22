#ifndef _CONTACT
#define _CONTACT

#include "Sort.h"

/**
* \author {DEVILLERS Alexandre, KRIMI Imran}
* \brief Class hérité de sort, permet de créé et gerer un sort contact.
*/
class Contact final: public Sort {
public:

    /**
    * \brief Constructeur par défaut
    */
    Contact();


    /**
    * \brief Actualise l'entite en fontion de la position passé en paramètre
    */
    void actualiseEntite(const complex<float> & pos);

    /**
    * \brief Lance le sort à la position donné
    */
    bool lance(const complex<float> & pos);

    /**
    * \brief Effectue les actions une fois que le sort à touché avec la 'i'eme entite (gestion des entites/récupération)
    */
    void aTouche(const unsigned int i);

private:



};

#endif
