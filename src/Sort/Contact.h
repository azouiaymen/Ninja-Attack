#ifndef _CONTACT
#define _CONTACT

#include "Sort.h"

/**
* \author {DEVILLERS Alexandre, KRIMI Imran}
* \brief Class h�rit� de sort, permet de cr�� et gerer un sort contact.
*/
class Contact final: public Sort {
public:

    /**
    * \brief Constructeur par d�faut
    */
    Contact();


    /**
    * \brief Actualise l'entite en fontion de la position pass� en param�tre
    */
    void actualiseEntite(const complex<float> & pos);

    /**
    * \brief Lance le sort � la position donn�
    */
    bool lance(const complex<float> & pos);

    /**
    * \brief Effectue les actions une fois que le sort � touch� avec la 'i'eme entite (gestion des entites/r�cup�ration)
    */
    void aTouche(const unsigned int i);

private:



};

#endif
