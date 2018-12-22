#ifndef _SORT
#define _SORT

#include "../Definition.h"
#include "../Entite.h"
#include "../Carte.h"
#include <vector>
#include <complex>
using namespace std;

/**
* \author {DEVILLERS Alexandre, KRIMI Imran}
* \brief Class hérité de sort, permet de créé et gerer un sort shuriken trois coups.
*/
class Sort {
public:

    /**
    * \brief Gere la colision avec un mur sur l'axe Y de la 'e'eme entite sur la tuile i,j de carte
    */
    Sort();

    /**
    * \brief Accesseur de degat
    */
    const int getDegat() const;
    /**
    * \brief Mutateur de degat
    */
    void setDegat(const int d);

    /**
    * \brief Accesseur de temps
    */
    const int getTemps() const;
    /**
    * \brief Mutateur de temps
    */
    void setTemps(const int t);

    /**
    * \brief Accesseur de recup
    */
    const int getRecup() const;
    /**
    * \brief Mutateur de recup
    */
    void setRecup(const int r);

    /**
    * \brief Accesseur de entites, ATTENTION IL EXISTE UNE VERSION NON CONST PAR REFERENCE
    */
    const vector<Entite> & getEntites() const;
    /**
    * \brief Accesseur de entites, ATTENTION RETURN NON CONST PAR REFERENCE
    */
    vector<Entite> & getEntites();

    /**
    * \brief Accesseur de entites (UNIQUEMENT VIRTUAL), ATTENTION IL EXISTE UNE VERSION NON CONST PAR REFERENCE
    */
    virtual const int getId() const;

    /**
    * \brief Ajoute une entite à entites
    */
    void addEntites(const Entite & e);
    /**
    * \brief Supprime la 'i'eme entite de entites
    */
    void supprEntites(const unsigned int i);


    /**
    * \brief Actualise la postion avec des vecteurs unitaires pour la 'e'eme entite de entites
    */
    virtual void actualisePosUnit(const unsigned int e, const Carte & carte);
    /**
    * \brief Si la 'e'eme entite est en fin de vie, appelle la precedure finDeVie
    */
    virtual bool actualiseFinDeVie(const unsigned int e);


    /**
    * \brief Effectue les actions une fois que le sort à touché avec la 'i'eme entite (gestion des entites/récupération)
    */
    virtual void aTouche(const unsigned int i);

protected:

    int degat; //!< \brief Dégats du sort
    int temps; //!< \brief Temps au dernier lancement du sort
    int recup; //!< \brief Temps de récuperation du sort
    vector<Entite> entites; //!< \brief Entites du sort


    /**
    * \brief Actualise la hitbox de la 'e'eme entite de entites
    */
    virtual void actualiseHitbox(const unsigned int e);

    /**
    * \brief Test la colision avec un mur sur l'axe X avec la 'e'eme entite
    */
    virtual void testColisionMurX(const unsigned int e, const Carte & carte);
    /**
    * \brief Test la colision avec un mur sur l'axe Y avec la 'e'eme entite
    */
    virtual void testColisionMurY(const unsigned int e, const Carte & carte);

    /**
    * \brief Gere la colision avec un mur sur l'axe X de la 'e'eme entite sur la tuile i,j de carte
    */
    virtual void colisionMurX(const unsigned int e, const int i, const int j, const Carte & carte);
    /**
    * \brief Gere la colision avec un mur sur l'axe Y de la 'e'eme entite sur la tuile i,j de carte
    */
    virtual void colisionMurY(const unsigned int e, const int i, const int j, const Carte & carte);

    /**
    * \brief Actualise la hitbox de la 'e'eme entite de entites
    */
    virtual void finDeVie(const unsigned int e);

};

#endif
