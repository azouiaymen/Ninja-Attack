#include "Personnage.h"
#include "../Carte.h"
#include <cassert>
#include <time.h>

Personnage::~Personnage() {

}

const int Personnage::getVie() const {
    return vie;
}

void Personnage::setVie(const int v) {
    vie = v;
}


const int Personnage::getVieMax() const {
    return vieMax;
}

void Personnage::setVieMax(const int v) {
    vieMax = v;
}


const bool Personnage::getSaut() const {
    return saut;
}

void Personnage::setSaut(const bool s) {
    saut = s;
}


const bool Personnage::getDSaut() const {
    return dSaut;
}

void Personnage::setDSaut(const bool s) {
    dSaut = s;
}


const bool Personnage::getRegardeDroite() const {
    return regardeDroite;
}

void Personnage::setRegardeDroite(const bool r) {
    regardeDroite = r;
}

const bool Personnage::getNage() const {
    return nage;
}

void Personnage::setNage(const bool r) {
    nage = r;
}


const Entite & Personnage::getEntite() const {
    return entite;
}

Entite & Personnage::getEntite() {
    return entite;
}

void Personnage::setEntite(const Entite & e) {
    entite = e;
}

vector<Sort*> Personnage::getSort() {
    vector<Sort*> sorts;
    return sorts;
}

const Tir * Personnage::getTir() const {
    return nullptr;
}

Tir * Personnage::getTir() {
    return nullptr;
}

const Contact * Personnage::getContact() const {
    return nullptr;
}

Contact * Personnage::getContact() {
    return nullptr;
}

const Dash * Personnage::getDash() const {
    return nullptr;
}

Dash * Personnage::getDash() {
    return nullptr;
}

const int Personnage::getId() const {
    return 0;
}




void Personnage::actualisePosUnit(const Carte & carte, vector<Sort*> sorts) {
    //On effectue les actualisations sur l'axe des X puis on verifie les colisions
    entite.actualiseUnitPosX();
    actualiseHitbox();
    testColisionMurX(carte);
    testColisionSortX(sorts);

    //On effectue les actualisations sur l'axe des Y puis on verifie les colisions
    entite.actualiseUnitPosY();
    actualiseHitbox();
    testColisionMurY(carte);
    testColisionSortY(sorts);
}




void Personnage::reflechis(const Entite & hero, const Carte & carte) {

}




void Personnage::saute() {
    if(saut) {
        entite.getVitesse().imag((-1/3.)*TBLOCK());
        saut = false;
    } else if(dSaut && entite.getVitesse().imag() >= -10) {
        entite.getVitesse().imag((-1/3.)*TBLOCK());
        dSaut = false;
    }
}

void Personnage::droite() {
    entite.getVitesse().real((1/8.)*TBLOCK());
    regardeDroite = true;
}

void Personnage::gauche() {
    entite.getVitesse().real((-1/8.)*TBLOCK());
    regardeDroite = false;
}

void Personnage::attend() {
    entite.getVitesse().real(0);
}


void Personnage::actualiseEntiteContact() {

}

void Personnage::actualiseEntiteDash() {

}




void Personnage::actualiseHitbox() {
    entite.getHitbox().setPos(entite.getPos());
}


void Personnage::testColisionMurX(const Carte & carte) {
    //On parcours les tuiles de la carte que la hitbox du joueur touche
    for(int i = ((int)(entite.getPos().real()/TBLOCK())); i <= ((int)((entite.getPos().real()+entite.getTaille().real())/TBLOCK())); i++) {
        for(int j = ((int)(entite.getPos().imag()/TBLOCK())); j <= ((int)((entite.getPos().imag()+entite.getTaille().imag())/TBLOCK())); j++) {
            if(i >= 0 && i < carte.getDim().real() && j >= 0 && j < carte.getDim().imag()) {
                //Si la tuile est 'dur' on effectue la colision avec un mur
                if(entite.getHitbox().touche(carte.getHitbox(i,j)) && carte.getHitbox(i, j).getType() == 1) {
                    colisionMurX(i, j, carte);
                }
                //Si la tuile est 'liquide' on met nage et saut à vrai
                if(entite.getHitbox().touche(carte.getHitbox(i,j)) && carte.getHitbox(i, j).getType() == 2) {
                    nage = true;
                    saut = true;
                }
            }
        }
    }
}

void Personnage::testColisionMurY(const Carte & carte) {
    //On parcours les tuiles de la carte que la hitbox du joueur touche
    for(int i = ((int)(entite.getPos().real()/TBLOCK())); i <= ((int)((entite.getPos().real()+entite.getTaille().real())/TBLOCK())); i++) {
        for(int j = ((int)(entite.getPos().imag()/TBLOCK())); j <= ((int)((entite.getPos().imag()+entite.getTaille().imag())/TBLOCK())); j++) {
            if(i >= 0 && i < carte.getDim().real() && j >= 0 && j < carte.getDim().imag()) {
                //Si la tuile est 'dur' on effectue la colision avec un mur
                if(entite.getHitbox().touche(carte.getHitbox(i,j)) && carte.getHitbox(i, j).getType() == 1) {
                    colisionMurY(i, j, carte);
                }
                //Si la tuile est 'liquide' on met nage et saut à vrai
                if(entite.getHitbox().touche(carte.getHitbox(i,j)) && carte.getHitbox(i, j).getType() == 2) {
                    nage = true;
                    saut = true;
                }
            }
        }
    }
}


void Personnage::colisionMurX(const int i, const int j, const Carte & carte) {
    //On ressort du mur
    if(entite.getVitesse().real() > 0) {
        entite.getPos().real( carte.getHitbox(i,j).getPos().real() - entite.getTaille().real() );
    } else if(entite.getVitesse().real() < 0) {
        entite.getPos().real( carte.getHitbox(i,j).getPos().real() + carte.getHitbox(i,j).getTaille().real() );
    }
}

void Personnage::colisionMurY(const int i, const int j, const Carte & carte) {
    //On ressort du mur et on met la vitesse vertical à 0
    //Si on allait vers le bas le saut et le double saut sont de nouveau disponible
    if(entite.getVitesse().imag() > 0) {
        entite.getPos().imag( carte.getHitbox(i,j).getPos().imag() - entite.getTaille().imag() );
        saut = dSaut = true;
    } else if(entite.getVitesse().imag() < 0) {
        entite.getPos().imag( carte.getHitbox(i,j).getPos().imag() + carte.getHitbox(i,j).getTaille().imag() );
    }
    entite.getVitesse().imag(0);
}




void Personnage::testColisionSortX(vector<Sort*> & sorts) {
    //Test de colision avec toutes les entites de tout les sorts
    for(unsigned int i = 0; i < sorts.size(); i++) {
        for(unsigned int j = 0; j < sorts[i]->getEntites().size(); j++) {
            unsigned int exSize = sorts[i]->getEntites().size();
            if(entite.getHitbox().touche(sorts[i]->getEntites()[j].getHitbox())) {
                colisionSortX(i, j, sorts);
                if(sorts[i]->getEntites().size() != exSize)
                    j--;
            }
        }
    }
}

void Personnage::testColisionSortY(vector<Sort*> & sorts) {
    //Test de colision avec toutes les entites de tout les sorts
    for(unsigned int i = 0; i < sorts.size(); i++) {
        for(unsigned int j = 0; j < sorts[i]->getEntites().size(); j++) {
            unsigned int exSize = sorts[i]->getEntites().size();
            if(entite.getHitbox().touche(sorts[i]->getEntites()[j].getHitbox())) {
                colisionSortY(i, j, sorts);
                if(sorts[i]->getEntites().size() != exSize)
                    j--;
            }
        }
    }
}


void Personnage::colisionSortX(const int i, const int j, vector<Sort*> & sorts) {
    //Le personnage perd sa vie en fonction des degats du sort
    vie-=sorts[i]->getDegat();
    sorts[i]->aTouche(j);
    //Si le sort est un sort du hero alors le dash du hero est de nouveau disponible
    if((sorts[i]->getId() == 3 || sorts[i]->getId() == 2 || sorts[i]->getId() == 1) && vie <= 0) {
        sorts[2]->setTemps((tempsEcoule()-sorts[2]->getRecup())+100);
    }
}

void Personnage::colisionSortY(const int i, const int j, vector<Sort*> & sorts) {
    //Le personnage perd sa vie en fonction des degats du sort
    vie-=sorts[i]->getDegat();
    sorts[i]->aTouche(j);
    //Si le sort est un sort du hero alors le dash du hero est de nouveau disponible
    if((sorts[i]->getId() == 3 || sorts[i]->getId() == 2 || sorts[i]->getId() == 1) && vie <= 0) {
        sorts[2]->setTemps((tempsEcoule()-sorts[2]->getRecup())+100);
    }
}




bool Personnage::testMort() {
    if(vie <= 0) {
        meurt();
        return true;
    }
    return false;
}

void Personnage::meurt() {

}
