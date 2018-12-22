#ifndef _JEU
#define _JEU

#include "Definition.h"
#include "Carte.h"
#include "Personnage/Personnage.h"
#include "Personnage/Hero.h"
#include "Personnage/Tortue.h"
#include "Personnage/Requin.h"
#include "Personnage/Aigle.h"
#include <vector>

/**
* \mainpage Ce projet a était réalisé par {DEVILLERS Alexandre, AZOUI Aymen, KRIMI Imran}
*/

/**
* \author {DEVILLERS Alexandre, AZOUI Aymen, KRIMI Imran}
* \brief Class principal, ou se passe tout les calculs, c'est le coeur du jeu
* \details
*/
class Jeu {
public:

    /**
    * \brief Fonction à appeler dans le main pour faire tourner le jeu
    */
    void boucle();

protected:

    int tempsFps; //!< \brief Temps avant la derniere actualisation de la boucle (sert à réguler les fps)
    int posCamX; //!< \brief Position de la caméra sur l'axe X
    int posCamY; //!< \brief Position de la caméra sur l'axe Y
    int etat; //!< \brief Etat, etat de la machine à etat, le jeu à différente scene selon l'etat
    int score; //!< \brief Score du joueur
    Carte carte; //!< \brief Carte qui est joué
    Hero hero; //!< \brief Hero joué par le joueur
    vector<Personnage*> enemis; //!< \brief Vector de pointeurs sur base, remplis par des enemis


    /**
    * \brief Pre actualise, gere les actualisations qui se font une fois par tick avant l'actualisation
    */
    void preActualise();
    /**
    * \brief Actualise de maniere unitaire (plusieurs fois par tick et syncrone) les données
    */
    void actualiseUnit();
    /**
    * \brief Post actualise, gere les actualisations qui se font une fois par tick apres l'actualisation
    */
    void postActualise();
    /**
    * \brief Gere toute l'actualisation c'est le coeur des calculs
    */
    void actualise();

    /**
    * \brief Gere la caméra
    */
    void testCam();
    /**
    * \brief Gere les eventuels sortie de carte (mort dans le vide...)
    */
    void testSortMap();
    /**
    * \brief Gere la mort et ses actions
    */
    void testMort();
    /**
    * \brief Si le hero à tué tout les ennemis et qu'il est sur un texture existante est étant '*' le niveau est fini ou score à 0
    */
    void testFin();

    /**
    * \brief Renvoie le meilleur score
    */
    int getBestScore();
    /**
    * \brief Renvoie le maximum des NbUnits de toutes les entites ainsi que remet les ItUnit à zero, doit être appellé une fois par tick
    */
    float getMaxNbUnitETResetItUnit();
    /**
    * \brief Renvoie les sorts du hero, ATTENTION VECTOR DE POINTEUR MANIER AVEC GRANDE PRECAUTION
    */
    vector<Sort*> getSortHero();
    /**
    * \brief Renvoie les sorts des enemis, ATTENTION VECTOR DE POINTEUR MANIER AVEC GRANDE PRECAUTION
    */
    vector<Sort*> getSortEnemis();

};




//################################# -- PARTIE AVEC TXT -- #################################//




#include "winTxt.h"

/**
* \author {DEVILLERS Alexandre, AZOUI Aymen, KRIMI Imran}
* \brief Class secondaire, hérité de la class Jeu, c'est la version texte
* \details
*/
class JeuTXT : public Jeu {
public:

    /**
    * \brief Fonction à appeler dans le main pour faire tourner le jeu
    */
    void boucle();

private:

    /**
    * \brief Gere l'affichage en entier, c'est ce qui est rajouté par cette class
    */
    void affiche(WinTXT & win);
    /**
    * \brief Gere l'affichage de la carte
    */
    void afficheCarte(WinTXT & win);
    /**
    * \brief Gere l'affichage du hero
    */
    void afficheHero(WinTXT & win);
    /**
    * \brief Gere l'affichage des enemis
    */
    void afficheEnemis(WinTXT & win);

};




//################################# -- PARTIE AVEC SDL -- #################################//




#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Sprite.h"
#include "DefinitionSDL.h"

/**
* \author {DEVILLERS Alexandre, AZOUI Aymen, KRIMI Imran}
* \brief Class la plus evolué, hérité de la class Jeu, c'est la version graphique
* \details
*/
class JeuSDL : public Jeu {
public:

    /**
    * \brief Fonction à appeler dans le main pour faire tourner le jeu
    */
    void boucle();

private:

    Sprite spriteMenu; //!< \brief Sprite du fond menu
    Sprite spriteBoutonContinuer; //!< \brief Sprite du bouton continuer
    Sprite spriteBoutonNouvellePartie; //!< \brief Sprite du bouton nouvelle partie
    Sprite spriteBoutonQuitter; //!< \brief Sprite du bouton quitter

    Sprite spriteFond1; //!< \brief Sprite de l'arriere plan le plus proche (arbres)
    Sprite spriteFond2; //!< \brief Sprite de l'arriere plan le 2eme plus proche (colines)
    Sprite spriteFond3; //!< \brief Sprite de l'arriere plan le plus loin (montagne)

    Sprite spriteEau; //!< \brief Sprite de l'eau en surface
    Sprite spriteSol; //!< \brief Sprite de l'herbe
    Sprite spritePierre; //!< \brief Sprite de la pierre
    Sprite spriteBlockEau; //!< \brief Sprite de l'eau en profondeur (pas surface)
    Sprite spriteFin; //!< \brief Sprite de la ligne d'arrivée
    Sprite spriteNuage; //!< \brief Sprite des nuages

    Sprite spriteShuriken; //!< \brief Sprite des shurikens
    Sprite spritePlume; //!< \brief Sprite des plumes
    Sprite spriteDash; //!< \brief Sprite du hero en dash
    Sprite spriteNinjaIdle; //!< \brief Sprite du hero à l'arret
    Sprite spriteNinjaMarche; //!< \brief Sprite du hero en marche
    Sprite spriteNinjaSaut; //!< \brief Sprite du hero en saut
    Sprite spriteNinjaSaut2; //!< \brief Sprite du hero en double saut

    Sprite spriteTortueIdle; //!< \brief Sprite d'une tortue à l'arret
    Sprite spriteTortueMarche; //!< \brief Sprite d'une tortue en marche

    Sprite spriteAigleIdle; //!< \brief Sprite de l'aigle

    Sprite spriteRequinIdle; //!< \brief Sprite du requin

    Sprite spriteBarreRouge; //!< \brief Sprite de la barre de vie rouge
    Sprite spriteBarreJaune; //!< \brief Sprite de la barre de vie jaune
    Sprite spriteBarreVert; //!< \brief Sprite de la barre de vie verte
    Sprite spriteBarreBlanc; //!< \brief Sprite de la barre de vie blanche
    Sprite spriteBarreRougeFond; //!< \brief Sprite du fond de la barre de vie rouge
    Sprite spriteBarreJauneFond; //!< \brief Sprite du fond de la barre de vie jaune
    Sprite spriteBarreVertFond; //!< \brief Sprite du fond de la barre de vie verte
    Sprite spriteBarreBlancFond; //!< \brief Sprite du fond de la barre de vie blanche

    Sprite spriteToucheDash; //!< \brief Sprite de l'IHM du sort dash
    Sprite spriteToucheShurikenCoups; //!< \brief Sprite de l'IHM du sort shuriken trois coup
    Sprite spriteToucheShurikenShot;  //!< \brief Sprite de l'IHM du sort shuriken shot gun

    Sprite spriteObstruction;  //!< \brief Sprite du voile rouge de l'IHM qui indique le sort en cours d'utilisation

    /**
    * \brief Initialisation des sprites
    */
    void initSprite(SDL_Renderer * renderer);

    /**
    * \brief Gere tout les affichages
    */
    void affiche();
    /**
    * \brief Gere l'affichage des barres de vies enemis
    */
    void afficheBarreVieEnemis();
    /**
    * \brief Gere l'affichage de la barre de vie du hero
    */
    void afficheBarreVieHero();
    /**
    * \brief Gere l'affichage des shurikens
    */
    void afficheShurikens();
    /**
    * \brief Gere l'affichage des plumes
    */
    void affichePlumes();
    /**
    * \brief Gere l'affichage des enemis
    */
    void afficheEnemis();
    /**
    * \brief Gere l'affichage du 'i'eme enemnis sous forme de tortue
    */
    void afficheTortue(const unsigned int i);
    /**
    * \brief Gere l'affichage du 'i'eme enemnis sous forme d'aigle
    */
    void afficheAigle(const unsigned int i);
    /**
    * \brief Gere l'affichage du 'i'eme enemnis sous forme de requin
    */
    void afficheRequin(const unsigned int i);
    /**
    * \brief Gere l'affichage du hero
    */
    void afficheHero();
    /**
    * \brief Gere l'affichage de la carte
    */
    void afficheCarte();
    /**
    * \brief Gere l'affichage du fond
    */
    void afficheFond();
    /**
    * \brief Gere l'affichage de l'IHM des sorts
    */
    void afficheSortIHM();
    /**
    * \brief Gere l'affichage du fond du menu
    */
    bool afficheMenu(bool quitter_menu);

    /**
    * \brief Renvoie la position de la souris
    */
    const complex<float> getPosSouris() const;

};

#endif
