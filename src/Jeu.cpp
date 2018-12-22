#include <cassert>
#include "Jeu.h"
#include <algorithm>
#include <fstream>
#include <cassert>
using namespace std;

void Jeu::boucle() {
    //DEBUT INIT
    bool quitter = false;
    carte = Carte("./data/Carte11.txt");
    tempsFps = 0;
    posCamX = 0;
    posCamY = 0;
    etat = 0;
    score = 3600;

    //Spawn les enemis et le hero selon la carte
    for(int i = 0; i < carte.getDim().real(); i++) {
        for(int j = 0; j < carte.getDim().imag(); j++) {
            if(carte.getTexture(i,j) == 't')
                enemis.push_back(new Tortue(complex<float>(i*TBLOCK(),j*TBLOCK())));
            if(carte.getTexture(i,j) == 'a')
                enemis.push_back(new Aigle(complex<float>(i*TBLOCK(),j*TBLOCK())));
            if(carte.getTexture(i,j) == 'r')
                enemis.push_back(new Requin(complex<float>(i*TBLOCK(),j*TBLOCK())));
            if(carte.getTexture(i,j) == 'h')
                hero.getEntite().setPos(complex<float>(i*TBLOCK(),j*TBLOCK()));
        }
    }
    //FIN INIT

    //DEBUT BOUCLE
    while(quitter == false) {

        //Régule les 60 fps
        if(tempsEcoule()-(tempsFps) > (float)(1000/60.)) {
        tempsFps = tempsEcoule();

            switch(etat){
            case 0 : //MENU
                posCamX = 0;
                posCamY = 0;
                score = 3600;

                if(etat == 1)
                {
                    etat = 2;
                } else if(etat == 2)
                {
                    //DESTRUCTION
                    for(unsigned int i = 0; i < enemis.size(); i++) {
                        delete enemis[i];
                        enemis[i] = NULL;
                        enemis.erase(enemis.begin()+i);
                        i--;
                    }
                    //FIN DESTRUCTION

                    //REINIT
                    hero.meurt();
                    etat = 2;
                    tempsFps = 0;
                    for(int i = 0; i < carte.getDim().real(); i++) {
                        for(int j = 0; j < carte.getDim().imag(); j++) {
                            if(carte.getTexture(i,j) == 't')
                                enemis.push_back(new Tortue(complex<float>(i*TBLOCK(),j*TBLOCK())));
                            if(carte.getTexture(i,j) == 'a')
                                enemis.push_back(new Aigle(complex<float>(i*TBLOCK(),j*TBLOCK())));
                            if(carte.getTexture(i,j) == 'r')
                                enemis.push_back(new Requin(complex<float>(i*TBLOCK(),j*TBLOCK())));
                            if(carte.getTexture(i,j) == 'h')
                                hero.getEntite().setPos(complex<float>(i*TBLOCK(),j*TBLOCK()));
                        }
                    }
                    //FINREINIT
                } else if(etat == 3)
                {
                    etat = 1;
                }
                break;
            case 1 : //SORTIE DU JEU
                for(unsigned int i = 0; i < enemis.size(); i++) {
                    delete enemis[i];
                    enemis[i] = NULL;
                }
                quitter = true;
                break;
            case 2: //BOUCLE POUR JOUER AU JEU
                //ACTUALISATION
                actualise();
                hero.actualiseEntiteShurikenTroisCoups();
                break;
            default:
                etat = 1;
                break;
            }
        }
    }
    //FIN BOUCLE

    //DEBUT DESTRUCTION
    for(unsigned int i = 0; i < enemis.size(); i++) {
        delete enemis[i];
        enemis[i] = NULL;
    }
    //FIN DESTRUCTION
}




void Jeu::preActualise() {
    //Un peu complexe à expliquer, mais on passe par toutes les entites pour actualiser leur vitesse on remet aussi le saut et la nage des persos à faux avant de repasser dans les tests
    hero.getEntite().actualiseVitesse();
    hero.setNage(false);
    hero.setSaut(false);

    for(unsigned int i = 0; i < enemis.size(); i++) {
        enemis[i]->getEntite().actualiseVitesse();
        enemis[i]->reflechis(hero.getEntite(), carte);
        enemis[i]->setNage(false);
        enemis[i]->actualiseEntiteContact();
        enemis[i]->actualiseEntiteDash();
        if(enemis[i]->getId() == 3) {
            for(unsigned int j = 0; j < enemis[i]->getDash()->getEntites().size(); j++) {
                enemis[i]->getDash()->getEntites()[j].actualiseVitesse();
                if(enemis[i]->getDash()->actualiseFinDeVie(j))
                    j--;
            }
        }
        if(enemis[i]->getId() == 4) {
            for(unsigned int j = 0; j < enemis[i]->getTir()->getEntites().size(); j++) {
                enemis[i]->getTir()->getEntites()[j].actualiseVitesse();
                if(enemis[i]->getTir()->actualiseFinDeVie(j))
                    j--;
            }
        }
    }

    for(unsigned int i = 0; i < hero.getShurikenTroisCoups()->getEntites().size(); i++) {
        hero.getShurikenTroisCoups()->getEntites()[i].actualiseVitesse();
        if(hero.getShurikenTroisCoups()->actualiseFinDeVie(i))
            i--;
    }

    for(unsigned int i = 0; i < hero.getShurikenShotGun()->getEntites().size(); i++) {
        hero.getShurikenShotGun()->getEntites()[i].actualiseVitesse();
        if(hero.getShurikenShotGun()->actualiseFinDeVie(i))
            i--;
    }

    for(unsigned int i = 0; i < hero.getDashHero()->getEntites().size(); i++) {
        hero.getDashHero()->getEntites()[i].actualiseVitesse();
        if(hero.getDashHero()->actualiseFinDeVie(i))
            i--;
    }
}

void Jeu::actualiseUnit() {
    /*On rentre dans une grande 'for' et on actualise de maniere unitaire chaque entite, ce qui permet de detecter les colisions de petits objets
    allant à une grande vitesse, ils ne peuvent se passer au dessus car leur vecteur est unitaire*/

    /*Pour cela on suit un paterne 'simple' on prend le plus grand 'x = maxnbunit' (le plus grand vecteur de tous) et on fait 'x' fois la boucle d'actualisation
    en actualisant les plus petits vecteurs à intervales régulier pour que tout les mouvements soit armonieux*/

    /*Surement le plus long à comprendre*/

    /*Les tests cam sont la pour assurer que la cam suit malgres les dash (mouvements rapide)*/
    vector<Sort*> sortsEnemis = getSortEnemis();
    vector<Sort*> sortsHero = getSortHero();
    int maxNbUnit = getMaxNbUnitETResetItUnit();

    for(int i = 0; i < maxNbUnit; i++) {
        if(i >= hero.getEntite().getItUnit() && hero.getEntite().getNbUnit() != 0) {
            hero.getEntite().setItUnit(hero.getEntite().getItUnit() + (float)maxNbUnit/hero.getEntite().getNbUnit());
            hero.actualisePosUnit(carte, sortsEnemis);
        }

        for(unsigned int j = 0; j < hero.getShurikenTroisCoups()->getEntites().size(); j++) {
            if(i >= hero.getShurikenTroisCoups()->getEntites()[j].getItUnit() && hero.getShurikenTroisCoups()->getEntites()[j].getNbUnit() != 0) {
                hero.getShurikenTroisCoups()->getEntites()[j].setItUnit(hero.getShurikenTroisCoups()->getEntites()[j].getItUnit() + (float)maxNbUnit/hero.getShurikenTroisCoups()->getEntites()[j].getNbUnit());
                hero.getShurikenTroisCoups()->actualisePosUnit(j, carte);
            }
        }

        for(unsigned int j = 0; j < hero.getShurikenShotGun()->getEntites().size(); j++) {
            if(i >= hero.getShurikenShotGun()->getEntites()[j].getItUnit() && hero.getShurikenShotGun()->getEntites()[j].getNbUnit() != 0) {
                hero.getShurikenShotGun()->getEntites()[j].setItUnit(hero.getShurikenShotGun()->getEntites()[j].getItUnit() + (float)maxNbUnit/hero.getShurikenShotGun()->getEntites()[j].getNbUnit());
                hero.getShurikenShotGun()->actualisePosUnit(j, carte);
            }
        }

        testCam();

        for(unsigned int j = 0; j < hero.getDashHero()->getEntites().size(); j++) {
            if(i >= hero.getDashHero()->getEntites()[j].getItUnit() && hero.getDashHero()->getEntites()[j].getNbUnit() != 0) {
                hero.getDashHero()->getEntites()[j].setItUnit(hero.getDashHero()->getEntites()[j].getItUnit() + (float)maxNbUnit/hero.getDashHero()->getEntites()[j].getNbUnit());
                hero.getDashHero()->actualisePosUnit(j, carte);
            }
        }

        for(unsigned int j = 0; j < enemis.size(); j++) {
            if(i >= enemis[j]->getEntite().getItUnit() && enemis[j]->getEntite().getNbUnit() != 0) {
                enemis[j]->getEntite().setItUnit(enemis[j]->getEntite().getItUnit() + (float)maxNbUnit/enemis[j]->getEntite().getNbUnit());
                enemis[j]->actualisePosUnit(carte, sortsHero);
            }
            if(enemis[j]->getId() == 2) {
                for(unsigned int k = 0; k < enemis[j]->getContact()->getEntites().size(); k++) {
                    if(i >= enemis[j]->getContact()->getEntites()[k].getItUnit() && enemis[j]->getContact()->getEntites()[k].getNbUnit() != 0) {
                        enemis[j]->getContact()->getEntites()[k].setItUnit(enemis[j]->getContact()->getEntites()[k].getItUnit() + (float)maxNbUnit/enemis[j]->getContact()->getEntites()[k].getNbUnit());
                        enemis[j]->getContact()->actualisePosUnit(k, carte);
                    }
                }
            }
            if(enemis[j]->getId() == 3) {
                for(unsigned int k = 0; k < enemis[j]->getDash()->getEntites().size(); k++) {
                    if(i >= enemis[j]->getDash()->getEntites()[k].getItUnit() && enemis[j]->getDash()->getEntites()[k].getNbUnit() != 0) {
                        enemis[j]->getDash()->getEntites()[k].setItUnit(enemis[j]->getDash()->getEntites()[k].getItUnit() + (float)maxNbUnit/enemis[j]->getDash()->getEntites()[k].getNbUnit());
                        enemis[j]->getDash()->actualisePosUnit(k, carte);
                    }
                }
            }
            if(enemis[j]->getId() == 4) {
                for(unsigned int k = 0; k < enemis[j]->getTir()->getEntites().size(); k++) {
                    if(i >= enemis[j]->getTir()->getEntites()[k].getItUnit() && enemis[j]->getTir()->getEntites()[k].getNbUnit() != 0) {
                        enemis[j]->getTir()->getEntites()[k].setItUnit(enemis[j]->getTir()->getEntites()[k].getItUnit() + (float)maxNbUnit/enemis[j]->getTir()->getEntites()[k].getNbUnit());
                        enemis[j]->getTir()->actualisePosUnit(k, carte);
                    }
                }
            }
        }
    }
    testCam();
}

void Jeu::postActualise() {
    /*Une fois le dash fini le hero suis le dash ce qui devrait contre-dire le mouvement "armonieux" de l'actualisation unitaire, mais en fesant ça apres les
    test de mort, le hero peut dasher sur un enemis sans forcement prendre de degat de cet enemis si il le tue car le hero reste "un tick en arriere"*/
    testSortMap();
    testMort();
    testFin();
    hero.actualiseEntiteDashHero();
}

void Jeu::actualise() {
    score--;
    preActualise();
    actualiseUnit();
    postActualise();
}


void Jeu::testCam() {
    //Si le hero sort de l'ecrant de 1/3 vers le haut bas gauche droite la postition de la camera change, si on est sur un bord de la carte on ne bouge plus la camera
    if(hero.getEntite().getHitbox().touche(Hitbox(complex<float>(-10000000, -10000000), complex<float>((DIMX()/3) + 10000000 + posCamX, 20000000), 0)))
        posCamX-= ((DIMX()/3)+1+posCamX) - hero.getEntite().getPos().real();
    if(hero.getEntite().getHitbox().touche(Hitbox(complex<float>((DIMX()*2/3) + posCamX, -10000000), complex<float>(20000000, 20000000), 0)))
        posCamX+= (hero.getEntite().getPos().real()+hero.getEntite().getTaille().real()) - ((DIMX()*2/3)+posCamX-1);
    if(DIMX()/TBLOCK() > carte.getDim().real()) {
        posCamX = 0;
    } else if(posCamX < 0) {
        posCamX = 0;
    } else if(posCamX > carte.getDim().real()*TBLOCK() - DIMX()) {
        posCamX = carte.getDim().real()*TBLOCK() - DIMX();
    }
    if(hero.getEntite().getHitbox().touche(Hitbox(complex<float>(-10000000, -10000000), complex<float>(20000000,(DIMX()/3) + 10000000 + posCamY), 0)))
        posCamY-= ((DIMY()/3)+1+posCamY) - hero.getEntite().getPos().imag();
    if(hero.getEntite().getHitbox().touche(Hitbox(complex<float>(-10000000, (DIMY()*2/3) + posCamY), complex<float>(20000000,20000000), 0)))
        posCamY+= (hero.getEntite().getPos().imag()+hero.getEntite().getTaille().imag()) - (((DIMY()*2/3)+posCamY)-1);
    if(DIMY()/TBLOCK() > carte.getDim().imag()) {
        posCamY = -(DIMY()/TBLOCK() - carte.getDim().imag())*TBLOCK();
    } else if(posCamY < 0) {
        posCamY = 0;
    } else if(posCamY > carte.getDim().imag()*TBLOCK() - DIMY()) {
        posCamY = carte.getDim().imag()*TBLOCK() - DIMY();
    }
}

void Jeu::testSortMap() {
    //Tout personnage sous la carte perd 10 points de vie par seconde
    if(hero.getEntite().getPos().imag() > carte.getDim().imag() * TBLOCK())
        hero.setVie(hero.getVie()-10);
    for(unsigned int i = 0; i < enemis.size(); i++) {
        if(enemis[i]->getEntite().getPos().imag() > carte.getDim().imag() * TBLOCK())
            enemis[i]->setVie(enemis[i]->getVie()-10);
    }
}

void Jeu::testMort() {
    //Si un personnage est mort on agit en conséquence
    for(unsigned int i = 0; i < enemis.size(); i++) {
        if(enemis[i]->testMort()) {
            delete enemis[i];
            enemis[i] = NULL;
            enemis.erase(enemis.begin()+i);
            i--;
        }
    }
    if(hero.testMort()) {
        etat = 0;
        //DESTRUCTION
        for(unsigned int i = 0; i < enemis.size(); i++) {
            delete enemis[i];
            enemis[i] = NULL;
            enemis.erase(enemis.begin()+i);
            i--;
        }
        //FIN DESTRUCTION

        //REINIT
        hero.meurt();
        tempsFps = 0;
        for(int i = 0; i < carte.getDim().real(); i++) {
            for(int j = 0; j < carte.getDim().imag(); j++) {
                if(carte.getTexture(i,j) == 't')
                    enemis.push_back(new Tortue(complex<float>(i*TBLOCK(),j*TBLOCK())));
                if(carte.getTexture(i,j) == 'a')
                    enemis.push_back(new Aigle(complex<float>(i*TBLOCK(),j*TBLOCK())));
                if(carte.getTexture(i,j) == 'r')
                    enemis.push_back(new Requin(complex<float>(i*TBLOCK(),j*TBLOCK())));
                if(carte.getTexture(i,j) == 'h')
                    hero.getEntite().setPos(complex<float>(i*TBLOCK(),j*TBLOCK()));
            }
        }
        //FINREINIT
    }
}

void Jeu::testFin() {
    //Si le score est 0 c'est la fin
    if(score <= 0) {
        hero.meurt();
        etat = 0;
    }
    //Si le hero à tué tout les ennemis et qu'il est sur un texture existante est étant '*' le niveau est fini
    if((int)(hero.getEntite().getPos().real()/TBLOCK()) < carte.getDim().real()
        && (int)(hero.getEntite().getPos().real()/TBLOCK()) >= 0
        && (int)(hero.getEntite().getPos().imag()/TBLOCK()) < carte.getDim().imag()
        && (int)(hero.getEntite().getPos().imag()/TBLOCK()) >= 0)
    {
        if(carte.getTexture((int)(hero.getEntite().getPos().real()/TBLOCK()), (int)(hero.getEntite().getPos().imag()/TBLOCK())) == '*' && enemis.size() == 0) {
            int best = getBestScore();

            ofstream outFichier ("./data/Score.txt");
            assert(outFichier.is_open());
            if(best < score) {
                outFichier << score;
            } else {
                outFichier << best;
            }
            outFichier.close();
            etat = 0;
        }
    }
}


int Jeu::getBestScore() {
    ifstream inFichier ("./data/Score.txt");
    assert(inFichier.is_open());
    int best = 0;
    inFichier >> best;
    inFichier.close();
    return best;
}

float Jeu::getMaxNbUnitETResetItUnit() {
    //On met tout dans un vector pour ensuite avoir le max et au passage on reset itunit à 0
    vector<float> nbUnits;
    nbUnits.push_back(hero.getEntite().getNbUnit());
    hero.getEntite().setItUnit(0);
    for(unsigned int i = 0; i < enemis.size(); i++) {
        nbUnits.push_back(enemis[i]->getEntite().getNbUnit());
        enemis[i]->getEntite().setItUnit(0);
    }
    vector<Sort*> sorts = getSortEnemis();
    vector<Sort*> sortsHero = getSortHero();
    sorts.insert(sorts.end(), sortsHero.begin(), sortsHero.end());
    for(unsigned int i = 0; i < sorts.size(); i++) {
        for(unsigned int j = 0; j < sorts[i]->getEntites().size(); j++) {
            nbUnits.push_back(sorts[i]->getEntites()[j].getNbUnit());
            sorts[i]->getEntites()[j].setItUnit(0);
        }
    }
    return *max_element(nbUnits.begin(), nbUnits.end());
}

vector<Sort*> Jeu::getSortHero() {
    return hero.getSort();
}

vector<Sort*> Jeu::getSortEnemis() {
    vector<Sort*> sorts;
    for(unsigned int i = 0; i < enemis.size(); i++) {
        vector<Sort*> sortsE = enemis[i]->getSort();
        sorts.insert(sorts.end(), sortsE.begin(), sortsE.end());
    }
    return sorts;
}




//################################# -- PARTIE AVEC TXT -- #################################//
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif




void JeuTXT::boucle() {
    //DEBUT INIT
    bool quitter = false;
    carte = Carte("./data/Carte11.txt");
    WinTXT win(carte.getDim().real(),carte.getDim().imag());
    etat = 2;
    tempsFps = 0;
    posCamX = 0;
    posCamY = 0;
    score = 3600;
    for(int i = 0; i < carte.getDim().real(); i++) {
        for(int j = 0; j < carte.getDim().imag(); j++) {
            if(carte.getTexture(i,j) == 't')
                enemis.push_back(new Tortue(complex<float>(i*TBLOCK(),j*TBLOCK())));
            if(carte.getTexture(i,j) == 'a')
                enemis.push_back(new Aigle(complex<float>(i*TBLOCK(),j*TBLOCK())));
            if(carte.getTexture(i,j) == 'r')
                enemis.push_back(new Requin(complex<float>(i*TBLOCK(),j*TBLOCK())));
            if(carte.getTexture(i,j) == 'h')
                hero.getEntite().setPos(complex<float>(i*TBLOCK(),j*TBLOCK()));
        }
    }
    //FIN INIT

    //DEBUT BOUCLE
    while(quitter == false && etat == 2) {
        if(tempsEcoule()-(tempsFps) > (float)(1000/60.)) {
            tempsFps = tempsEcoule();
            hero.getEntite().getVitesse().real(0);
            //INTPUT
            switch(win.getCh())
            {
            case 'z':
                hero.saute();
                break;
            case 'q':
                hero.gauche();
                break;
            case 'd':
                hero.droite();
                break;
            case 'x':
                quitter = true;
                break;
            }
            //ACTUALISATION
            actualise();
            hero.actualiseEntiteShurikenTroisCoups();
            //AFFICHAGE
            affiche(win);
        }
    }
    //FIN BOUCLE

    //DEBUT DESTRUCTION
    termClear();
    for(unsigned int i = 0; i < enemis.size(); i++) {
        delete enemis[i];
        enemis[i] = NULL;
    }
    //FIN DESTRUCTION
}

void JeuTXT::affiche(WinTXT & win) {
    termClear();
    win.clear(' ');

    afficheCarte(win);
    afficheEnemis(win);
    afficheHero(win);

    win.draw();
    #ifdef _WIN32
    Sleep(16);
    #else
    usleep(16);
    #endif // WIN32
}

void JeuTXT::afficheCarte(WinTXT & win) {
    for(int i = 0; i < carte.getDim().real(); i++) {
        for(int j = 0; j < carte.getDim().imag(); j++) {
            if(carte.getHitbox(i,j).getType() == 1)
                win.print(i,j,'#');
            if(carte.getHitbox(i,j).getType() == 2)
                win.print(i,j,'~');
        }
    }
}

void JeuTXT::afficheHero(WinTXT & win) {
    win.print((int)(hero.getEntite().getPos().real()/TBLOCK()) ,(int)(hero.getEntite().getPos().imag()/TBLOCK()),'P');
}

void JeuTXT::afficheEnemis(WinTXT & win) {
    for(unsigned int i = 0; i < enemis.size(); i++) {
        switch(enemis[i]->getId()) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            win.print((int)(enemis[i]->getEntite().getPos().real()/TBLOCK()) ,(int)(enemis[i]->getEntite().getPos().imag()/TBLOCK()),'T');
            break;
        case 3:
            win.print((int)(enemis[i]->getEntite().getPos().real()/TBLOCK()) ,(int)(enemis[i]->getEntite().getPos().imag()/TBLOCK()),'R');
            break;
        case 4:
            win.print((int)(enemis[i]->getEntite().getPos().real()/TBLOCK()) ,(int)(enemis[i]->getEntite().getPos().imag()/TBLOCK()),'A');
            break;
        default:
            break;
        }
    }
}




//################################# -- PARTIE AVEC SDL -- #################################//




void JeuSDL::boucle() {
    //DEBUT INIT SDL
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Event e;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if(TTF_Init() != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }
    window = SDL_CreateWindow("Ninjattack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DIMX()*AFFCOEF(), DIMY()*AFFCOEF(), SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_BORDERLESS );
    if(AFFDIMX() > 1024)
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    initSprite(renderer);

    TTF_Font* police = TTF_OpenFont( "./data/police.ttf", 72*AFFCOEF());
    SDL_Color couleur = { 50, 50, 50, 255};
    SDL_Surface * textSurface;
    SDL_Texture* texteTexture;
    SDL_Rect texteRect;
    texteRect.x = 5;
    texteRect.y = 5;
    //FIN INIT SDL

    //DEBUT INIT
    complex<float> boutonContinuerPos, boutonContinuerTaille, boutonQuitterPos, boutonQuitterTaille, boutonNouvellePartiePos, boutonNouvellePartieTaille;
    boutonContinuerTaille = boutonQuitterTaille = boutonNouvellePartieTaille = complex<float>(DIMX()/4,DIMX()/16);
    boutonContinuerPos = complex<float>(DIMX()/2 -DIMX()/8, 2*DIMY()/5);
    boutonNouvellePartiePos = complex<float>(DIMX()/2 -DIMX()/8, 3*DIMY()/5);
    boutonQuitterPos = complex<float>(DIMX()/2 -DIMX()/8, 4*DIMY()/5);
    bool quitter = false;
    bool sourisClicNMoins1 = false;
    carte = Carte("./data/Carte1.txt");
    tempsFps = 0;
    posCamX = 0;
    posCamY = 0;
    etat = 0;
    score = 3600;
    for(int i = 0; i < carte.getDim().real(); i++) {
        for(int j = 0; j < carte.getDim().imag(); j++) {
            if(carte.getTexture(i,j) == 't')
                enemis.push_back(new Tortue(complex<float>(i*TBLOCK(),j*TBLOCK())));
            if(carte.getTexture(i,j) == 'a')
                enemis.push_back(new Aigle(complex<float>(i*TBLOCK(),j*TBLOCK())));
            if(carte.getTexture(i,j) == 'r')
                enemis.push_back(new Requin(complex<float>(i*TBLOCK(),j*TBLOCK())));
            if(carte.getTexture(i,j) == 'h')
                hero.getEntite().setPos(complex<float>(i*TBLOCK(),j*TBLOCK()));
        }
    }
    //FIN INIT

    //DEBUT BOUCLE
    while(quitter == false) {
        if(SDL_GetTicks()-(tempsFps) > (float)(1000/60.)) {
        tempsFps = SDL_GetTicks();
            switch(etat){
            case 0 :
                SDL_PollEvent(&e);

                posCamX = 0;
                posCamY = 0;

                if(boutonContinuerPos.real() <= getPosSouris().real()
                    && boutonContinuerPos.real() + boutonContinuerTaille.real() > getPosSouris().real()
                    && boutonContinuerPos.imag() <= getPosSouris().imag()
                    && boutonContinuerPos.imag() + boutonContinuerTaille.imag() > getPosSouris().imag()
                    && !SDL_GetMouseState(NULL, NULL)
                    && SDL_BUTTON(SDL_BUTTON_LEFT)
                    && sourisClicNMoins1)
                {
                    if(enemis.size() == 0 || score == 0) {
                        //DESTRUCTION
                        for(unsigned int i = 0; i < enemis.size(); i++) {
                            delete enemis[i];
                            enemis[i] = NULL;
                            enemis.erase(enemis.begin()+i);
                            i--;
                        }
                        //FIN DESTRUCTION

                        //REINIT
                        hero.meurt();
                        etat = 2;
                        tempsFps = 0;
                        score = 3600;
                        for(int i = 0; i < carte.getDim().real(); i++) {
                            for(int j = 0; j < carte.getDim().imag(); j++) {
                                if(carte.getTexture(i,j) == 't')
                                    enemis.push_back(new Tortue(complex<float>(i*TBLOCK(),j*TBLOCK())));
                                if(carte.getTexture(i,j) == 'a')
                                    enemis.push_back(new Aigle(complex<float>(i*TBLOCK(),j*TBLOCK())));
                                if(carte.getTexture(i,j) == 'r')
                                    enemis.push_back(new Requin(complex<float>(i*TBLOCK(),j*TBLOCK())));
                                if(carte.getTexture(i,j) == 'h')
                                    hero.getEntite().setPos(complex<float>(i*TBLOCK(),j*TBLOCK()));
                            }
                        }
                        //FINREINIT
                    }
                    etat = 2;
                } else if(boutonNouvellePartiePos.real() <= getPosSouris().real()
                    && boutonNouvellePartiePos.real() + boutonNouvellePartieTaille.real() > getPosSouris().real()
                    && boutonNouvellePartiePos.imag() <= getPosSouris().imag()
                    && boutonNouvellePartiePos.imag() + boutonNouvellePartieTaille.imag() > getPosSouris().imag()
                    && !SDL_GetMouseState(NULL, NULL)
                    && SDL_BUTTON(SDL_BUTTON_LEFT)
                    && sourisClicNMoins1)
                {
                    //DESTRUCTION
                    for(unsigned int i = 0; i < enemis.size(); i++) {
                        delete enemis[i];
                        enemis[i] = NULL;
                        enemis.erase(enemis.begin()+i);
                        i--;
                    }
                    //FIN DESTRUCTION

                    //REINIT
                    hero.meurt();
                    etat = 2;
                    tempsFps = 0;
                    score = 3600;
                    for(int i = 0; i < carte.getDim().real(); i++) {
                        for(int j = 0; j < carte.getDim().imag(); j++) {
                            if(carte.getTexture(i,j) == 't')
                                enemis.push_back(new Tortue(complex<float>(i*TBLOCK(),j*TBLOCK())));
                            if(carte.getTexture(i,j) == 'a')
                                enemis.push_back(new Aigle(complex<float>(i*TBLOCK(),j*TBLOCK())));
                            if(carte.getTexture(i,j) == 'r')
                                enemis.push_back(new Requin(complex<float>(i*TBLOCK(),j*TBLOCK())));
                            if(carte.getTexture(i,j) == 'h')
                                hero.getEntite().setPos(complex<float>(i*TBLOCK(),j*TBLOCK()));
                        }
                    }
                    //FINREINIT
                } else if(boutonQuitterPos.real() <= getPosSouris().real()
                          && boutonQuitterPos.real() + boutonQuitterTaille.real() > getPosSouris().real()
                          && boutonQuitterPos.imag() <= getPosSouris().imag()
                          && boutonQuitterPos.imag() + boutonQuitterTaille.imag() > getPosSouris().imag()
                          && !SDL_GetMouseState(NULL, NULL)
                          && SDL_BUTTON(SDL_BUTTON_LEFT)
                          && sourisClicNMoins1)
                {
                    etat = 1;
                }

                SDL_RenderClear(renderer);
                spriteMenu.afficher(0,0,AFFDIMX(),AFFDIMY());
                spriteBoutonContinuer.afficher(boutonContinuerPos.real()*AFFCOEF(), boutonContinuerPos.imag()*AFFCOEF(), boutonContinuerTaille.real()*AFFCOEF(), boutonContinuerTaille.imag()*AFFCOEF());
                spriteBoutonNouvellePartie.afficher(boutonNouvellePartiePos.real()*AFFCOEF(), boutonNouvellePartiePos.imag()*AFFCOEF(), boutonNouvellePartieTaille.real()*AFFCOEF(), boutonNouvellePartieTaille.imag()*AFFCOEF());
                spriteBoutonQuitter.afficher(boutonQuitterPos.real()*AFFCOEF(), boutonQuitterPos.imag()*AFFCOEF(), boutonQuitterTaille.real()*AFFCOEF(), boutonQuitterTaille.imag()*AFFCOEF());

                texteRect.y = (DIMY()*7/32)*AFFCOEF();

                textSurface = TTF_RenderText_Blended(police, string("Best : "+to_string(getBestScore())).c_str(), couleur);
                texteTexture = SDL_CreateTextureFromSurface( renderer, textSurface);
                SDL_FreeSurface(textSurface);
                SDL_QueryTexture( texteTexture, NULL, NULL, &texteRect.w, &texteRect.h );
                SDL_RenderCopy( renderer, texteTexture, nullptr, &texteRect);
                SDL_DestroyTexture(texteTexture);

                if(enemis.size() == 0 && score > 0) {
                    texteRect.x = (DIMX()/2)*AFFCOEF();
                    textSurface = TTF_RenderText_Blended(police, string("Score : "+to_string(score)).c_str(), couleur);
                    texteTexture = SDL_CreateTextureFromSurface( renderer, textSurface);
                    SDL_FreeSurface(textSurface);
                    SDL_QueryTexture( texteTexture, NULL, NULL, &texteRect.w, &texteRect.h );
                    SDL_RenderCopy( renderer, texteTexture, nullptr, &texteRect);
                    SDL_DestroyTexture(texteTexture);
                } else if(score == 0) {
                    texteRect.x = (DIMX()/2)*AFFCOEF();
                    textSurface = TTF_RenderText_Blended(police, string("Score : "+to_string(score)).c_str(), couleur);
                    texteTexture = SDL_CreateTextureFromSurface( renderer, textSurface);
                    SDL_FreeSurface(textSurface);
                    SDL_QueryTexture( texteTexture, NULL, NULL, &texteRect.w, &texteRect.h );
                    SDL_RenderCopy( renderer, texteTexture, nullptr, &texteRect);
                    SDL_DestroyTexture(texteTexture);
                }

                texteRect.x = 5;
                texteRect.y = 5;

                SDL_RenderPresent(renderer);
                break;
            case 1 : //SORTIE DU JEU
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                for(unsigned int i = 0; i < enemis.size(); i++) {
                    delete enemis[i];
                    enemis[i] = NULL;
                }
                quitter = true;
                break;
            case 2: //BOUCLE POUR JOUER AU JEU
                //ACTUALISATION
                actualise();
                hero.actualiseEntiteShurikenTroisCoups(getPosSouris()); //Pas dans actualise car il y a du SDL dedant (sort asyncrone)
                //FIN ACTUALISATION

                //PARTIE INPUT
                SDL_PollEvent(&e);
                if (e.type == SDL_QUIT)
                    etat = 1;
                if (keys[SDL_SCANCODE_ESCAPE])
                    etat = 0;
                if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_SPACE]) {
                    hero.saute();
                }
                if (keys[SDL_SCANCODE_A]){
                    hero.gauche();
                } else if(keys[SDL_SCANCODE_D]) {
                    hero.droite();
                } else {
                    hero.attend();
                }
                if (keys[SDL_SCANCODE_LSHIFT]){
                    hero.lanceDashHero(getPosSouris());
                }
                if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                    hero.lanceShurikenTroisCoups(getPosSouris());
                if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
                    hero.lanceShurikenShotGun(getPosSouris());
                //FIN PARTIE INPUT

                //AFFICHAGE
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 175, 225, 250, 255);
                affiche();

                textSurface = TTF_RenderText_Blended(police, string("Score : "+to_string(score)).c_str(), couleur);
                texteTexture = SDL_CreateTextureFromSurface( renderer, textSurface);
                SDL_FreeSurface(textSurface);
                SDL_QueryTexture( texteTexture, NULL, NULL, &texteRect.w, &texteRect.h );
                SDL_RenderCopy( renderer, texteTexture, nullptr, &texteRect);
                SDL_DestroyTexture(texteTexture);

                SDL_RenderPresent(renderer);
                //FIN AFFICHAGE
                break;
            }

            sourisClicNMoins1 = false;
            if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                sourisClicNMoins1 = true;
            }
        }
    }
    //FIN BOUCLE

    //DEBUT DESTRUCTION
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    for(unsigned int i = 0; i < enemis.size(); i++) {
        delete enemis[i];
        enemis[i] = NULL;
    }
    //FIN DESTRUCTION
}

void JeuSDL::initSprite(SDL_Renderer * renderer) {

    spriteFond1.init(renderer, "./data/Fond Arbre.png", 1, 1);
    spriteFond2.init(renderer, "./data/Fond Coline.png", 1, 1);
    spriteFond3.init(renderer, "./data/Fond Montagne.png", 1, 1);

    spriteMenu.init(renderer, "./data/Menu.png", 1, 1);
    spriteBoutonContinuer.init(renderer, "./data/Bouton Continuer.png", 1, 1);
    spriteBoutonNouvellePartie.init(renderer, "./data/Bouton Nouvelle Partie.png", 1, 1);
    spriteBoutonQuitter.init(renderer, "./data/Bouton Quitter.png", 1, 1);

    spriteEau.init(renderer, "./data/Eau.png", 8, 4);
    spriteSol.init(renderer, "./data/Sol.png", 1, 1);
    spritePierre.init(renderer, "./data/Pierre.png", 1, 1);
    spriteNuage.init(renderer, "./data/Nuage.png", 1, 1);
    spriteBlockEau.init(renderer, "./data/BlockEau.png", 1, 1);
    spriteFin.init(renderer, "./data/Fin.png", 1, 1);

    spriteShuriken.init(renderer, "./data/Shuriken.png", 1, 1);
    spritePlume.init(renderer, "./data/Plume.png", 1, 1);
    spriteDash.init(renderer, "./data/Ninja Dash.png", 1, 1);

    spriteNinjaIdle.init(renderer, "./data/Ninja Idle.png", 2, 4);
    spriteNinjaMarche.init(renderer, "./data/Ninja Marche.png", 2, 6);
    spriteNinjaSaut.init(renderer, "./data/Ninja Saut.png", 1, 1);
    spriteNinjaSaut2.init(renderer, "./data/Ninja Jump 2.png", 4, 6);

    spriteTortueIdle.init(renderer, "./data/Tortue Idle.png", 1, 1);
    spriteTortueMarche.init(renderer, "./data/Tortue Marche.png", 2, 6);

    spriteAigleIdle.init(renderer, "./data/Aigle Idle.png", 2, 3);

    spriteRequinIdle.init(renderer, "./data/Requin Idle.png", 13, 6);

    spriteBarreRouge.init(renderer, "./data/Barre Rouge.png", 1, 1);
    spriteBarreVert.init(renderer, "./data/Barre Vert.png", 1, 1);
    spriteBarreJaune.init(renderer, "./data/Barre Jaune.png", 1, 1);
    spriteBarreBlanc.init(renderer, "./data/Barre Blanc.png", 1, 1);

    spriteBarreRougeFond.init(renderer, "./data/Barre Rouge Fond.png", 1, 1);
    spriteBarreVertFond.init(renderer, "./data/Barre Vert Fond.png", 1, 1);
    spriteBarreJauneFond.init(renderer, "./data/Barre Jaune Fond.png", 1, 1);
    spriteBarreBlancFond.init(renderer, "./data/Barre Blanc Fond.png", 1, 1);

    spriteToucheDash.init(renderer, "./data/Dash.png", 1, 1);
    spriteToucheShurikenCoups.init(renderer, "./data/Shuriken Coups.png", 1, 1);
    spriteToucheShurikenShot.init(renderer, "./data/Shuriken Shot.png", 1, 1);

    spriteObstruction.init(renderer, "./data/Obstruction.png", 1, 1);
}

void JeuSDL::affiche() {
    afficheFond();
    afficheCarte();
    afficheEnemis();
    afficheBarreVieEnemis();
    afficheHero();
    afficheShurikens();
    affichePlumes();
    afficheBarreVieHero();
    afficheSortIHM();
}

void JeuSDL::afficheBarreVieHero() {
    //Si la vie du hero est sous les 50 la vie est rouge
    if(hero.getVie() > 50) {
        spriteBarreBlancFond.afficher(((hero.getEntite().getPos().real() + hero.getEntite().getTaille().real()/2) - TBLOCK()/2 - posCamX)*AFFCOEF(), (hero.getEntite().getPos().imag() - (24/64.)*TBLOCK() - posCamY)*AFFCOEF(), TBLOCK()*AFFCOEF(), (8/32.)*TBLOCK()*AFFCOEF());
        spriteBarreBlanc.afficher(((hero.getEntite().getPos().real() + hero.getEntite().getTaille().real()/2) - TBLOCK()/2 - posCamX)*AFFCOEF() + (1/30.)*TBLOCK()*AFFCOEF(), (hero.getEntite().getPos().imag() - (24/64.)*TBLOCK() - posCamY)*AFFCOEF() + (1/30.)*TBLOCK()*AFFCOEF(), ((float)hero.getVie()/hero.getVieMax())*(28/30.)*TBLOCK()*AFFCOEF(), (6/32.)*TBLOCK()*AFFCOEF());
    } else {
        spriteBarreRougeFond.afficher(((hero.getEntite().getPos().real() + hero.getEntite().getTaille().real()/2) - TBLOCK()/2 - posCamX)*AFFCOEF(), (hero.getEntite().getPos().imag() - (24/64.)*TBLOCK() - posCamY)*AFFCOEF(), TBLOCK()*AFFCOEF(), (8/32.)*TBLOCK()*AFFCOEF());
        if(hero.getVie() >=0)
            spriteBarreRouge.afficher(((hero.getEntite().getPos().real() + hero.getEntite().getTaille().real()/2) - TBLOCK()/2 - posCamX)*AFFCOEF() + (1/30.)*TBLOCK()*AFFCOEF(), (hero.getEntite().getPos().imag() - (24/64.)*TBLOCK() - posCamY)*AFFCOEF() + (1/30.)*TBLOCK()*AFFCOEF(), ((float)hero.getVie()/hero.getVieMax())*(28/30.)*TBLOCK()*AFFCOEF(), (6/32.)*TBLOCK()*AFFCOEF());
    }
}

void JeuSDL::afficheBarreVieEnemis() {
    //Si l'enemis est sous les 50% des points de vie max alors la barre est jaune, et sous les 50 elle est rouge
    for(unsigned int i = 0; i < enemis.size(); i++) {
        if(enemis[i]->getVie() > enemis[i]->getVieMax()/2) {
            spriteBarreVertFond.afficher(((enemis[i]->getEntite().getPos().real() + enemis[i]->getEntite().getTaille().real()/2) - TBLOCK()/2 - posCamX)*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - (24/64.)*TBLOCK() - posCamY)*AFFCOEF(), TBLOCK()*AFFCOEF(), (8/32.)*TBLOCK()*AFFCOEF());
            spriteBarreVert.afficher(((enemis[i]->getEntite().getPos().real() + enemis[i]->getEntite().getTaille().real()/2) - TBLOCK()/2 - posCamX)*AFFCOEF() + (1/30.)*TBLOCK()*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - (24/64.)*TBLOCK() - posCamY)*AFFCOEF() + (1/30.)*TBLOCK()*AFFCOEF(), ((float)enemis[i]->getVie()/enemis[i]->getVieMax())*(28/30.)*TBLOCK()*AFFCOEF(), (6/32.)*TBLOCK()*AFFCOEF());
        } else if (enemis[i]->getVie() > 50) {
            spriteBarreJauneFond.afficher(((enemis[i]->getEntite().getPos().real() + enemis[i]->getEntite().getTaille().real()/2) - TBLOCK()/2 - posCamX)*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - (24/64.)*TBLOCK() - posCamY)*AFFCOEF(), TBLOCK()*AFFCOEF(), (8/32.)*TBLOCK()*AFFCOEF());
            spriteBarreJaune.afficher(((enemis[i]->getEntite().getPos().real() + enemis[i]->getEntite().getTaille().real()/2) - TBLOCK()/2 - posCamX)*AFFCOEF() + (1/30.)*TBLOCK()*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - (24/64.)*TBLOCK() - posCamY)*AFFCOEF() + (1/30.)*TBLOCK()*AFFCOEF(), ((float)enemis[i]->getVie()/enemis[i]->getVieMax())*(28/30.)*TBLOCK()*AFFCOEF(), (6/32.)*TBLOCK()*AFFCOEF());
        } else {
            spriteBarreRougeFond.afficher(((enemis[i]->getEntite().getPos().real() + enemis[i]->getEntite().getTaille().real()/2) - TBLOCK()/2 - posCamX)*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - (24/64.)*TBLOCK() - posCamY)*AFFCOEF(), TBLOCK()*AFFCOEF(), (8/32.)*TBLOCK()*AFFCOEF());
            if(enemis[i]->getVie() >= 0)
                spriteBarreRouge.afficher(((enemis[i]->getEntite().getPos().real() + enemis[i]->getEntite().getTaille().real()/2) - TBLOCK()/2 - posCamX)*AFFCOEF() + (1/30.)*TBLOCK()*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - (24/64.)*TBLOCK() - posCamY)*AFFCOEF() + (1/30.)*TBLOCK()*AFFCOEF(), ((float)enemis[i]->getVie()/enemis[i]->getVieMax())*(28/30.)*TBLOCK()*AFFCOEF(), (6/32.)*TBLOCK()*AFFCOEF());
        }
    }
}

void JeuSDL::afficheShurikens() {
    for(unsigned int i = 0; i < hero.getShurikenTroisCoups()->getEntites().size(); i++) {
        spriteShuriken.afficher((hero.getShurikenTroisCoups()->getEntites()[i].getPos().real() - posCamX)*AFFCOEF(), (hero.getShurikenTroisCoups()->getEntites()[i].getPos().imag() - posCamY)*AFFCOEF(), (hero.getShurikenTroisCoups()->getEntites()[i].getTaille().real())*AFFCOEF(), (hero.getShurikenTroisCoups()->getEntites()[i].getTaille().imag())*AFFCOEF());
    }
    for(unsigned int i = 0; i < hero.getShurikenShotGun()->getEntites().size(); i++) {
        spriteShuriken.afficher((hero.getShurikenShotGun()->getEntites()[i].getPos().real() - posCamX)*AFFCOEF(), (hero.getShurikenShotGun()->getEntites()[i].getPos().imag() - posCamY)*AFFCOEF(), (hero.getShurikenShotGun()->getEntites()[i].getTaille().real())*AFFCOEF(), (hero.getShurikenShotGun()->getEntites()[i].getTaille().imag())*AFFCOEF());
    }
}

void JeuSDL::affichePlumes() {
    for(unsigned int i = 0; i < enemis.size(); i++) {
        if(enemis[i]->getId() == 4) {
            for(unsigned int j = 0; j < enemis[i]->getTir()->getEntites().size(); j++) {
                spritePlume.afficher((enemis[i]->getTir()->getEntites()[j].getPos().real() - posCamX)*AFFCOEF(), (enemis[i]->getTir()->getEntites()[j].getPos().imag() - posCamY)*AFFCOEF(), (enemis[i]->getTir()->getEntites()[j].getTaille().real())*AFFCOEF(), (enemis[i]->getTir()->getEntites()[j].getTaille().imag())*AFFCOEF());
            }
        }
    }
}

void JeuSDL::afficheEnemis() {
    for(unsigned int i = 0; i < enemis.size(); i++) {
        switch(enemis[i]->getId()) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            afficheTortue(i);
            break;
        case 3:
            afficheRequin(i);
            break;
        case 4:
            afficheAigle(i);
            break;
        default:
            break;
        }
    }
}

void JeuSDL::afficheTortue(const unsigned int i) {
    if(enemis[i]->getRegardeDroite()) {
        if(enemis[i]->getEntite().getVitesse().real() != 0) {
            spriteTortueMarche.afficher((enemis[i]->getEntite().getPos().real() - posCamX)*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - posCamY)*AFFCOEF(), (enemis[i]->getEntite().getTaille().real())*AFFCOEF(), (enemis[i]->getEntite().getTaille().imag())*AFFCOEF(), true);
        } else {
            spriteTortueIdle.afficher((enemis[i]->getEntite().getPos().real() - posCamX)*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - posCamY)*AFFCOEF(), (enemis[i]->getEntite().getTaille().real())*AFFCOEF(), (enemis[i]->getEntite().getTaille().imag())*AFFCOEF(), true);
        }
    } else {
        if(enemis[i]->getEntite().getVitesse().real() != 0) {
            spriteTortueMarche.afficher((enemis[i]->getEntite().getPos().real() - posCamX)*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - posCamY)*AFFCOEF(), (enemis[i]->getEntite().getTaille().real())*AFFCOEF(), (enemis[i]->getEntite().getTaille().imag())*AFFCOEF());
        } else {
            spriteTortueIdle.afficher((enemis[i]->getEntite().getPos().real() - posCamX)*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - posCamY)*AFFCOEF(), (enemis[i]->getEntite().getTaille().real())*AFFCOEF(), (enemis[i]->getEntite().getTaille().imag())*AFFCOEF());
        }
    }
}

void JeuSDL::afficheAigle(const unsigned int i) {
    if(enemis[i]->getRegardeDroite()) {
        spriteAigleIdle.afficher((enemis[i]->getEntite().getPos().real() - posCamX)*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - posCamY)*AFFCOEF(), (enemis[i]->getEntite().getTaille().real())*AFFCOEF(), (enemis[i]->getEntite().getTaille().imag())*AFFCOEF());
    } else {
        spriteAigleIdle.afficher((enemis[i]->getEntite().getPos().real() - posCamX)*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - posCamY)*AFFCOEF(), (enemis[i]->getEntite().getTaille().real())*AFFCOEF(), (enemis[i]->getEntite().getTaille().imag())*AFFCOEF(), true);
    }
}

void JeuSDL::afficheRequin(const unsigned int i) {
    if(enemis[i]->getRegardeDroite()) {
        spriteRequinIdle.afficher((enemis[i]->getEntite().getPos().real() - posCamX)*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - posCamY)*AFFCOEF(), (enemis[i]->getEntite().getTaille().real())*AFFCOEF(), (enemis[i]->getEntite().getTaille().imag())*AFFCOEF());
    } else {
        spriteRequinIdle.afficher((enemis[i]->getEntite().getPos().real() - posCamX)*AFFCOEF(), (enemis[i]->getEntite().getPos().imag() - posCamY)*AFFCOEF(), (enemis[i]->getEntite().getTaille().real())*AFFCOEF(), (enemis[i]->getEntite().getTaille().imag())*AFFCOEF(), true);
    }
}

void JeuSDL::afficheHero() {
    //Toute ses conditions determine quelle sprite afficher pour le hero, saut/ marche/ idle ...
    if(hero.getDashHero()->getEntites().size() <= 0) {
        if(hero.getRegardeDroite()) {
            if(hero.getSaut()) {
                if(hero.getEntite().getVitesse().real() != 0){
                    spriteNinjaMarche.afficher(((hero.getEntite().getPos().real() - posCamX)+ (-2/9.)*TBLOCK())*AFFCOEF(), (hero.getEntite().getPos().imag() - posCamY)*AFFCOEF(), (70/64.)*TBLOCK()*AFFCOEF(), (112/64.)*TBLOCK()*AFFCOEF());
                } else {
                    spriteNinjaIdle.afficher(((hero.getEntite().getPos().real() - posCamX)+ (-2/9.)*TBLOCK())*AFFCOEF(), (hero.getEntite().getPos().imag() - posCamY)*AFFCOEF(), (70/64.)*TBLOCK()*AFFCOEF(), (112/64.)*TBLOCK()*AFFCOEF());
                }
            } else if(hero.getSaut() == false && hero.getDSaut()) {
                spriteNinjaSaut.afficher(((hero.getEntite().getPos().real() - posCamX)+ (-2/9.)*TBLOCK())*AFFCOEF(), (hero.getEntite().getPos().imag() - posCamY)*AFFCOEF(), (70/64.)*TBLOCK()*AFFCOEF(), (112/64.)*TBLOCK()*AFFCOEF());
            } else {
                spriteNinjaSaut2.afficher(((hero.getEntite().getPos().real() - posCamX)+ (-3/9.)*TBLOCK())*AFFCOEF(), (hero.getEntite().getPos().imag() - posCamY)*AFFCOEF(), (112/64.)*TBLOCK()*AFFCOEF(), (112/64.)*TBLOCK()*AFFCOEF());
            }
        } else {
            if(hero.getSaut()) {
                if(hero.getEntite().getVitesse().real() != 0){
                    spriteNinjaMarche.afficher(((hero.getEntite().getPos().real() - posCamX))*AFFCOEF(), (hero.getEntite().getPos().imag() - posCamY)*AFFCOEF(), (70/64.)*TBLOCK()*AFFCOEF(), (112/64.)*TBLOCK()*AFFCOEF(), true);
                } else {
                    spriteNinjaIdle.afficher(((hero.getEntite().getPos().real() - posCamX))*AFFCOEF(), (hero.getEntite().getPos().imag() - posCamY)*AFFCOEF(), (70/64.)*TBLOCK()*AFFCOEF(), (112/64.)*TBLOCK()*AFFCOEF(), true);
                }
            } else if(hero.getSaut() == false && hero.getDSaut()) {
                spriteNinjaSaut.afficher(((hero.getEntite().getPos().real() - posCamX))*AFFCOEF(), (hero.getEntite().getPos().imag() - posCamY)*AFFCOEF(), (70/64.)*TBLOCK()*AFFCOEF(), (112/64.)*TBLOCK()*AFFCOEF(), true);
            } else {
                spriteNinjaSaut2.afficher(((hero.getEntite().getPos().real() - posCamX))*AFFCOEF(), (hero.getEntite().getPos().imag() - posCamY)*AFFCOEF(), (112/64.)*TBLOCK()*AFFCOEF(), (112/64.)*TBLOCK()*AFFCOEF(), true);
            }
        }
    } else {
        if(hero.getDashHero()->getEntites()[0].getVitesse().real() > 0) {
            spriteDash.afficher(((hero.getEntite().getPos().real() - posCamX))*AFFCOEF(), (hero.getEntite().getPos().imag() - posCamY)*AFFCOEF(), (64/64.)*TBLOCK()*AFFCOEF(), (120/64.)*TBLOCK()*AFFCOEF());
        } else {
            spriteDash.afficher(((hero.getEntite().getPos().real() - posCamX))*AFFCOEF(), (hero.getEntite().getPos().imag() - posCamY)*AFFCOEF(), (64/64.)*TBLOCK()*AFFCOEF(), (120/64.)*TBLOCK()*AFFCOEF(), true);
        }
    }
}

void JeuSDL::afficheCarte() {
    for(int i = 0; i < carte.getDim().real(); i++) {
        for(int j = 0; j < carte.getDim().imag(); j++) {
            switch(carte.getTexture(i,j)) {
            case '_':
                spriteSol.afficher(complex<float>((i*TBLOCK() - posCamX)*AFFCOEF(), (j*TBLOCK() - posCamY)*AFFCOEF()), complex<float>(TBLOCK()*AFFCOEF(),TBLOCK()*AFFCOEF()));
                break;
            case '~':
                spriteEau.afficher(complex<float>((i*TBLOCK() - posCamX)*AFFCOEF(), (j*TBLOCK() - posCamY)*AFFCOEF()), complex<float>(TBLOCK()*AFFCOEF(),TBLOCK()*AFFCOEF()));
                break;
            case '-':
                spritePierre.afficher(complex<float>((i*TBLOCK() - posCamX)*AFFCOEF(), (j*TBLOCK() - posCamY)*AFFCOEF()), complex<float>(TBLOCK()*AFFCOEF(),TBLOCK()*AFFCOEF()));
                break;
            case '+':
                spriteBlockEau.afficher(complex<float>((i*TBLOCK() - posCamX)*AFFCOEF(), (j*TBLOCK() - posCamY)*AFFCOEF()), complex<float>(TBLOCK()*AFFCOEF(),TBLOCK()*AFFCOEF()));
                break;
            case 'n':
                spriteNuage.afficher(complex<float>((i*TBLOCK() - posCamX)*AFFCOEF(), (j*TBLOCK() - posCamY)*AFFCOEF()), complex<float>(TBLOCK()*AFFCOEF(),TBLOCK()*AFFCOEF()));
                break;
            case '*':
                spriteFin.afficher(complex<float>((i*TBLOCK() - posCamX)*AFFCOEF(), (j*TBLOCK() - posCamY)*AFFCOEF()), complex<float>(TBLOCK()*AFFCOEF(),TBLOCK()*AFFCOEF()));
                if(enemis.size() > 0)
                    spriteObstruction.afficher(complex<float>((i*TBLOCK() - posCamX)*AFFCOEF(), (j*TBLOCK() - posCamY)*AFFCOEF()), complex<float>(TBLOCK()*AFFCOEF(),TBLOCK()*AFFCOEF()));
                break;
            }
        }
    }
}

void JeuSDL::afficheFond() {
    //Affiche les différents fond avec un décalé dépendant la profondeur
    spriteFond3.afficher((((int)(-posCamX*AFFCOEF())/4))%AFFDIMX(), ((carte.getDim().imag()*TBLOCK() - posCamY)*AFFCOEF() - AFFDIMY()) - ((carte.getDim().imag()*TBLOCK() - DIMY()) - posCamY)/(1*AFFCOEF()), AFFDIMX(), AFFDIMY());
    spriteFond3.afficher((((int)(-posCamX*AFFCOEF())/4))%AFFDIMX()+AFFDIMX(), ((carte.getDim().imag()*TBLOCK() - posCamY)*AFFCOEF() - AFFDIMY())  - ((carte.getDim().imag()*TBLOCK() - DIMY()) - posCamY)/(1*AFFCOEF()), AFFDIMX(), AFFDIMY());
    spriteFond2.afficher((((int)(-posCamX*AFFCOEF())/3))%AFFDIMX(), ((carte.getDim().imag()*TBLOCK() - posCamY)*AFFCOEF() - AFFDIMY()) - ((carte.getDim().imag()*TBLOCK() - DIMY()) - posCamY)/(2*AFFCOEF()), AFFDIMX(), AFFDIMY());
    spriteFond2.afficher((((int)(-posCamX*AFFCOEF())/3))%AFFDIMX()+AFFDIMX(), ((carte.getDim().imag()*TBLOCK() - posCamY)*AFFCOEF() - AFFDIMY()) - ((carte.getDim().imag()*TBLOCK() - DIMY()) - posCamY)/(2*AFFCOEF()), AFFDIMX(), AFFDIMY());
    spriteFond1.afficher((((int)(-posCamX*AFFCOEF())/2))%AFFDIMX(), ((carte.getDim().imag()*TBLOCK() - posCamY)*AFFCOEF() - AFFDIMY()) - ((carte.getDim().imag()*TBLOCK() - DIMY()) - posCamY)/(3*AFFCOEF()), AFFDIMX(), AFFDIMY());
    spriteFond1.afficher((((int)(-posCamX*AFFCOEF())/2))%AFFDIMX()+AFFDIMX(), ((carte.getDim().imag()*TBLOCK() - posCamY)*AFFCOEF() - AFFDIMY()) - ((carte.getDim().imag()*TBLOCK() - DIMY()) - posCamY)/(3*AFFCOEF()), AFFDIMX(), AFFDIMY());
}

void JeuSDL::afficheSortIHM() {
    //Affiche la disponibilité des sorts
    spriteToucheDash.afficher((64*1/4)*AFFCOEF(), AFFDIMY()-((64/4)+64)*AFFCOEF(), 64*AFFCOEF(), 64*AFFCOEF());
    if((tempsEcoule()-hero.getDashHero()->getTemps()) < hero.getDashHero()->getRecup())
        spriteObstruction.afficher((64*1/4)*AFFCOEF(), AFFDIMY()-(64/4)*AFFCOEF(), 64*AFFCOEF(), -64*AFFCOEF()*(1-((float)((tempsEcoule()-hero.getDashHero()->getTemps())/hero.getDashHero()->getRecup()))));

    spriteToucheShurikenCoups.afficher((64*6/4)*AFFCOEF(), AFFDIMY()-((64/4)+64)*AFFCOEF(), 64*AFFCOEF(), 64*AFFCOEF());
    if((tempsEcoule()-hero.getShurikenTroisCoups()->getTemps()) < hero.getShurikenTroisCoups()->getRecup())
        spriteObstruction.afficher((64*6/4)*AFFCOEF(), AFFDIMY()-(64/4)*AFFCOEF(), 64*AFFCOEF(), -64*AFFCOEF()*(1-((float)((tempsEcoule()-hero.getShurikenTroisCoups()->getTemps())/hero.getShurikenTroisCoups()->getRecup()))));

    spriteToucheShurikenShot.afficher((64*11/4)*AFFCOEF(), AFFDIMY()-((64/4)+64)*AFFCOEF(), 64*AFFCOEF(), 64*AFFCOEF());
    if((tempsEcoule()-hero.getShurikenShotGun()->getTemps()) < hero.getShurikenShotGun()->getRecup())
        spriteObstruction.afficher((64*11/4)*AFFCOEF(), AFFDIMY()-(64/4)*AFFCOEF(), 64*AFFCOEF(), -64*AFFCOEF()*(1-((float)((tempsEcoule()-hero.getShurikenShotGun()->getTemps())/hero.getShurikenShotGun()->getRecup()))));
}


const complex<float> JeuSDL::getPosSouris() const {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX,&mouseY);
    mouseX/=AFFCOEF();
    mouseY/=AFFCOEF();
    mouseX+=posCamX;
    mouseY+=posCamY;
    return complex<float>(mouseX,mouseY);
}
