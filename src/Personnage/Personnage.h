#ifndef _PERSONNAGE
#define _PERSONNAGE

#include "../Definition.h"
#include "../Entite.h"
#include "../Sort/Sort.h"
#include "../Sort/ShurikenTroisCoups.h"
#include "../Sort/ShurikenShotGun.h"
#include "../Sort/DashHero.h"
#include "../Sort/Contact.h"
#include "../Sort/Dash.h"
#include "../Sort/Tir.h"
#include "../Carte.h"
#include <vector>
using namespace std;

/**
* \author {DEVILLERS Alexandre, AZOUI Aymen}
* \brief Class personnage, class mere du hero et des enemis, ne doit pas être instancié autrement que par une class fille.
*/
class Personnage {
public:

    /**
    * \brief Destructeur
    */
    virtual ~Personnage();

    /**
    * \brief Accesseur de 'vie'
    */
    const int getVie() const;
    /**
    * \brief Mutateur de 'vie'
    */
    void setVie(const int v);

    /**
    * \brief Accesseur de 'vieMax'
    */
    const int getVieMax() const;
    /**
    * \brief Mutateur de 'vieMax'
    */
    void setVieMax(const int v);

    /**
    * \brief Accesseur de 'saut'
    */
    const bool getSaut() const;
    /**
    * \brief Mutateur de 'saut'
    */
    void setSaut(const bool s);

    /**
    * \brief Accesseur de 'dSaut'
    */
    const bool getDSaut() const;
    /**
    * \brief Mutateur de 'dSaut'
    */
    void setDSaut(const bool s);

    /**
    * \brief Accesseur de 'regardeDroite'
    */
    const bool getRegardeDroite() const;
    /**
    * \brief Mutateur de 'regardeDroite'
    */
    void setRegardeDroite(const bool r);

    /**
    * \brief Accesseur de 'nage'
    */
    const bool getNage() const;
    /**
    * \brief Mutateur de 'nage'
    */
    void setNage(const bool r);

    /**
    * \brief Accesseur de 'entite', ATTENTION IL EXISTE UN VERSION NON CONST PAR REFERENCE
    */
    const Entite & getEntite() const;
    /**
    * \brief Accesseur de 'entite', ATTENTION VERSION NON CONST PAR REFERENCE
    */
    Entite & getEntite();
    /**
    * \brief Mutateur de 'entite'
    */
    void setEntite(const Entite & e);

    /**
    * \brief Permet d'obtenir dans un vector de pointeur de sort les sorts du personnage (uniquement virtual), ATTENTION A MANIPULER AVEC PRECAUTION CAR VECTOR DE POINTEURS
    */
    virtual vector<Sort*> getSort();
    /**
    * \brief Permet d'obtenir l'id (un entier unique pour chaque class héritées), uniquement virtual
    */
    virtual const int getId() const;

    /**
    * \brief Permet de récuperer le pointeur du sort Tir(UNIQUEMENT VIRTUAL), ATTENTION A MANIPULER AVEC PRECAUTION CAR EXISTE UNE VERSION POINTEUR NON CONST
    */
    virtual const Tir * getTir() const;
    /**
    * \brief Permet de récuperer le pointeur du sort Tir(UNIQUEMENT VIRTUAL), ATTENTION A MANIPULER AVEC PRECAUTION CAR POINTEUR NON CONST
    */
    virtual Tir * getTir();

    /**
    * \brief Permet de récuperer le pointeur du sort Contact(UNIQUEMENT VIRTUAL), ATTENTION A MANIPULER AVEC PRECAUTION CAR EXISTE UNE VERSION POINTEUR NON CONST
    */
    virtual const Contact * getContact() const;
    /**
    * \brief Permet de récuperer le pointeur du sort Contact(UNIQUEMENT VIRTUAL), ATTENTION A MANIPULER AVEC PRECAUTION CAR POINTEUR NON CONST
    */
    virtual Contact * getContact();

    /**
    * \brief Permet de récuperer le pointeur du sort Dash(UNIQUEMENT VIRTUAL), ATTENTION A MANIPULER AVEC PRECAUTION CAR EXISTE UNE VERSION POINTEUR NON CONST
    */
    virtual const Dash * getDash() const;
    /**
    * \brief Permet de récuperer le pointeur du sort Dash(UNIQUEMENT VIRTUAL), ATTENTION A MANIPULER AVEC PRECAUTION CAR POINTEUR NON CONST
    */
    virtual Dash * getDash();

    /**
    * \brief Actualise la position avec des vecteurs unitaire
    */
    void actualisePosUnit(const Carte & carte, vector<Sort*> sorts);

    /**
    * \brief L'IA du personnage, avec comme paramètres l'entite cible (le hero) et la carte (UNIQUEMENT VIRTUAL)
    */
    virtual void reflechis(const Entite & hero, const Carte & carte);


    /**
    * \brief Fait sauter le personnage
    */
    void saute();
    /**
    * \brief Fait aller à droite le personnage
    */
    void droite();
    /**
    * \brief Fait aller à gauche le personnage
    */
    void gauche();
    /**
    * \brief Immobilise le personnage
    */
    void attend();


    /**
    * \brief Permet l'actualisation de l'entite pour le sort contact (UNIQUEMENT VIRTUAL) (obligatoire pour manipuler des pointeur sur personnage de manière generique)
    */
    virtual void actualiseEntiteContact();
    /**
    * \brief Permet l'actualisation de l'entite pour le sort dash (UNIQUEMENT VIRTUAL) (obligatoire pour manipuler des pointeur sur personnage de manière generique)
    */
    virtual void actualiseEntiteDash();


    /**
    * \brief Test si le personnage est mort, si true est renvoyer on appelle aussi meurt()
    */
    bool testMort();
    /**
    * \brief Effectue les actions suivant la mort du personnage (UNIQUEMENT VIRTUAL)
    */
    virtual void meurt();

protected:

    int vie; //!< \brief Vie actuelle
    int vieMax; //!< \brief Vie maximum
    bool saut; //!< \brief True si le saut est disponible
    bool dSaut; //!< \brief True si le double saut est disponible
    bool regardeDroite; //!< \brief True si le personnage regarde à droite
    bool nage; //!< \brief True si le personnage est dans un liquide
    Entite entite; //!< \brief L'entite du personnage


    /**
    * \brief Actualise la position de la hitbox par rapport à l'entite
    */
    void actualiseHitbox();

    /**
    * \brief Test si il y a une colision avec un mur en X
    */
    void testColisionMurX(const Carte & carte);
    /**
    * \brief Test si il y a une colision avec un mur en Y
    */
    void testColisionMurY(const Carte & carte);

    /**
    * \brief Applique la colision en X avec la tuile en i,j
    */
    void colisionMurX(const int i, const int j, const Carte & carte);
    /**
    * \brief Applique la colision en Y avec la tuile en i,j
    */
    void colisionMurY(const int i, const int j, const Carte & carte);


    /**
    * \brief Test si il y a une colision avec un sort en X
    */
    void testColisionSortX(vector<Sort*> & sorts);
    /**
    * \brief Test si il y a une colision avec un sort en y
    */
    void testColisionSortY(vector<Sort*> & sorts);

    /**
    * \brief Applique la colision en X avec la 'j'eme entite du 'i'eme sort
    */
    void colisionSortX(const int i, const int j, vector<Sort*> & sorts);
    /**
    * \brief Applique la colision en Y avec la 'j'eme entite du 'i'eme sort
    */
    void colisionSortY(const int i, const int j, vector<Sort*> & sorts);

};

#endif
