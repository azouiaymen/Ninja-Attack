#ifndef _ENTITE
#define _ENTITE

#include "Definition.h"
#include "Hitbox.h"
using namespace std;

/**
* \author {DEVILLERS Alexandre}
* \brief Class qui permet la gestion d'entite
*/
class Entite
{
public:

    /**
    * \brief Constructeur par defaut
    */
    Entite();
    /**
    * \brief Constructeur avec initialisation de tout les paramètres passé en arguments
    * @param n pour ne
    * @param d pour duree
    * @param g pour gravite
    * @param p pour pos
    * @param ta pour taille
    * @param v pour vitesse
    * @param a pour acceler
    * @param h pour hitbox
    */
    Entite(const int n, const int d, const float g, const complex<float> p, const complex<float> ta, const complex<float> v, const complex<float> a, const Hitbox & h);
    /**
    * \brief Constructeur par copie
    */
    Entite(const Entite & e);


    /**
    * \brief Accesseur de ne
    */
    const int getNe() const;
    /**
    * \brief Mutateur de ne
    */
    void setNe(const int n);

    /**
    * \brief Accesseur de duree
    */
    const int getDuree() const;
    /**
    * \brief Mutateur de duree
    */
    void setDuree(const int d);

    /**
    * \brief Accesseur de itUnit
    */
    const float getItUnit() const;
    /**
    * \brief Mutateur de itUnit
    */
    void setItUnit(const float i);

    /**
    * \brief Accesseur de gravite
    */
    const float getGravite() const;
    /**
    * \brief Mutateur de gravite
    */
    void setGravite(const float g);

    /**
    * \brief Accesseur de pos, ATTENTION IL EXISTE UNE VERSION NON CONST PAR REFERENCE
    */
    const complex<float> & getPos()const;
    /**
    * \brief Accesseur de pos, ATTENTION VERSION NON CONST PAR REFERENCE
    */
    complex<float> & getPos();
    /**
    * \brief Mutateur de pos
    */
    void setPos(const complex<float> & cplx);

    /**
    * \brief Accesseur de vitesse, ATTENTION IL EXISTE UNE VERSION NON CONST PAR REFERENCE
    */
    const complex<float> & getVitesse()const;
    /**
    * \brief Accesseur de vitesse, ATTENTION VERSION NON CONST PAR REFERENCE
    */
    complex<float> & getVitesse();
    /**
    * \brief Mutateur de vitesse
    */
    void setVitesse(const complex<float> & cplx);

    /**
    * \brief Accesseur de acceler, ATTENTION IL EXISTE UNE VERSION NON CONST PAR REFERENCE
    */
    const complex<float> & getAcceler()const;
    /**
    * \brief Accesseur de acceler, ATTENTION VERSION NON CONST PAR REFERENCE
    */
    complex<float> & getAcceler();
    /**
    * \brief Mutateur de acceler
    */
    void setAcceler(const complex<float> & cplx);

    /**
    * \brief Accesseur de taille, ATTENTION IL EXISTE UNE VERSION NON CONST PAR REFERENCE
    */
    const complex<float> & getTaille()const;
    /**
    * \brief Accesseur de taille, ATTENTION VERSION NON CONST PAR REFERENCE
    */
    complex<float> & getTaille();
    /**
    * \brief Mutateur de taille
    */
    void setTaille(const complex<float> & cplx);

    /**
    * \brief Accesseur de hitbox, ATTENTION IL EXISTE UNE VERSION NON CONST PAR REFERENCE
    */
    const Hitbox & getHitbox() const;
    /**
    * \brief Accesseur de hitbox, ATTENTION VERSION NON CONST PAR REFERENCE
    */
    Hitbox & getHitbox();
    /**
    * \brief Mutateur de hitbox
    */
    void setHitbox(const Hitbox & e);


    /**
    * \brief Met à jour la vitesse avec l'acceleration (à faire qu'une fois par tick)
    */
    void actualiseVitesse();
    /**
    * \brief Met à jour la position en X de maniere unitaire (à faire NbUnit fois par tick)
    */
    void actualiseUnitPosX();
    /**
    * \brief Met à jour la position en Y de maniere unitaire (à faire NbUnit fois par tick)
    */
    void actualiseUnitPosY();
    /**
    * \brief Permet d'obtenir le nombre de fois que les actualisations unit doivent être fait par tick
    */
    const float getNbUnit() const;


private:

    int ne; //!< \brief Temps ou l'entite est né
    int duree; //!< \brief Durée de vie de l'entite
    float itUnit; //!< \brief Itérateur pour savoir à combien de actualise pos unit on en est dans le tick
    float gravite; //!< \brief Force de la gravite
    complex<float> pos; //!< \brief Position de l'entite
    complex<float> vitesse; //!< \brief Vitesse de l'entite
    complex<float> acceler; //!< \brief Acceleration de l'entite
    complex<float> taille; //!< \brief Taille de l'entite
    Hitbox hitbox; //!< \brief Hitbox de l'entite

};

#endif
