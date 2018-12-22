#ifndef _CARTE
#define _CARTE

#include "Definition.h"
#include "Hitbox.h"
#include <string>
#include <vector>
#include <complex>
#include <iostream>
using namespace std;

/**
* \author {DEVILLERS Alexandre}
* \brief Petite class bien pratique pour generer une carte depuis un fichier txt
*/
class Carte {
public:

    /**
    * \brief Constructeur par defaut
    */
    Carte();
    /**
    * \brief Constructeur avec le nom du fichier de la map
    * \detailsLe Fichier txt doit avoir sur la premiere ligne les dimentions x y, sur la 2eme ligne les caracteres représentant les tuiles dur, 3eme ligne les tuiles liquides, et enfin la map, ou chaque caractere est une tuile
    */
    Carte(const string nomFichier);


    /**
    * \brief Permet d'obtenir les dimentions de la carte
    */
    const complex<int> getDim() const;

    /**
    * \brief Permet d'obtenir le caractere représentant la tuile en x,y
    */
    const char & getTexture(const unsigned int x, const unsigned int y) const;

    /**
    * \brief Permet d'obtenir la hitboc de la tuile en x,y
    */
    const Hitbox & getHitbox(const unsigned int x, const unsigned int y) const;

private:

    complex<int> dim; //!< \brief Dimentions de la map
    vector< vector<char> > texture; //!< \brief Tableau 2D avec les caracteres représentant les textures de la map
    vector< vector<Hitbox> > hitbox; //!< \brief Tableau 2D avec les hitbox des tuiles de la map

};

#endif
