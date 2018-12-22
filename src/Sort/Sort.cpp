#include "Sort.h"
#include <math.h>
#include <stdlib.h>
#include <cassert>

#ifndef M_PI
 #define M_PI 3.1415926535
#endif

Sort::Sort() {
    degat = 0;
    temps = 0;
    recup = -1;
}




const int Sort::getDegat() const {
    return degat;
}

void Sort::setDegat(const int d) {
    degat = d;
}


const int Sort::getTemps() const {
    return temps;
}

void Sort::setTemps(const int t) {
    temps = t;
}


const int Sort::getRecup() const {
    return recup;
}

void Sort::setRecup(const int r) {
    recup = r;
}


const vector<Entite> & Sort::getEntites() const {
    return entites;
}

vector<Entite> & Sort::getEntites() {
    return entites;
}


const int Sort::getId() const {
    return 0;
}


void Sort::addEntites(const Entite & e) {
    entites.push_back(e);
}

void Sort::supprEntites(const unsigned int i) {
    assert(!(i > entites.size()));
    entites.erase(entites.begin() + i);
}




void Sort::actualisePosUnit(const unsigned int e, const Carte & carte) {
    assert(!(e > entites.size()));
    entites[e].actualiseUnitPosX();
    actualiseHitbox(e);
    testColisionMurX(e, carte);
    entites[e].actualiseUnitPosY();
    actualiseHitbox(e);
    testColisionMurY(e, carte);
}

bool Sort::actualiseFinDeVie(const unsigned int e) {
    assert(!(e > entites.size()));
    if(tempsEcoule() - entites[e].getNe() >= entites[e].getDuree() && entites[e].getDuree() >= 0) {
        finDeVie(e);
        return true;
    }
    return false;
}


void Sort::aTouche(const unsigned int i) {
    assert(!(i > entites.size()));
    entites.erase(getEntites().begin()+i);
}




void Sort::actualiseHitbox(const unsigned int e) {
    assert(!(e > entites.size()));
    entites[e].getHitbox().setPos(entites[e].getPos());
}


void Sort::testColisionMurX(const unsigned int e, const Carte & carte) {
    assert(!(e > entites.size()));
    //On parcours les tuiles de la carte que la 'e'eme hitbox du sort touche
    for(int i = ((int)(entites[e].getPos().real()/TBLOCK())) -2; i <= ((int)(entites[e].getPos().real()/TBLOCK())) +2; i++) {
        for(int j = ((int)(entites[e].getPos().imag()/TBLOCK())) -2; j <= ((int)(entites[e].getPos().imag()/TBLOCK())) +2; j++) {
            if(i >= 0 && i < carte.getDim().real() && j >= 0 && j < carte.getDim().imag()) {
                //Si elle est de type 1 on agit en consequence
                if(entites[e].getHitbox().touche(carte.getHitbox(i,j)) && carte.getHitbox(i, j).getType() == 1) {
                    colisionMurX(e, i, j, carte);
                }
            }
        }
    }
}

void Sort::testColisionMurY(const unsigned int e, const Carte & carte) {
    assert(!(e > entites.size()));
    //On parcours les tuiles de la carte que la 'e'eme hitbox du sort touche
    for(int i = ((int)(entites[e].getPos().real()/TBLOCK())) -2; i <= ((int)(entites[e].getPos().real()/TBLOCK())) +2; i++) {
        for(int j = ((int)(entites[e].getPos().imag()/TBLOCK())) -2; j <= ((int)(entites[e].getPos().imag()/TBLOCK())) +2; j++) {
            if(i >= 0 && i < carte.getDim().real() && j >= 0 && j < carte.getDim().imag()) {
                //Si elle est de type 1 on agit en consequence
                if(entites[e].getHitbox().touche(carte.getHitbox(i,j)) && carte.getHitbox(i, j).getType() == 1) {
                    colisionMurY(e, i, j, carte);
                }
            }
        }
    }
}

void Sort::colisionMurX(const unsigned int e, const int i, const int j, const Carte & carte) {
    assert(!(e > entites.size()));
    //On ressort du mur
    if(entites[e].getVitesse().real() > 0) {
        entites[e].getPos().real( carte.getHitbox(i,j).getPos().real() - entites[e].getTaille().real() );
    } else if(entites[e].getVitesse().real() < 0) {
        entites[e].getPos().real( carte.getHitbox(i,j).getPos().real() + carte.getHitbox(i,j).getTaille().real() );
    }
}

void Sort::colisionMurY(const unsigned int e, const int i, const int j, const Carte & carte) {
    assert(!(e > entites.size()));
    //On ressort du mur et on met la vitesse vertical à 0
    if(entites[e].getVitesse().imag() > 0) {
        entites[e].getPos().imag( carte.getHitbox(i,j).getPos().imag() - entites[e].getTaille().imag() );
    } else if(entites[e].getVitesse().imag() < 0) {
        entites[e].getPos().imag( carte.getHitbox(i,j).getPos().imag() + carte.getHitbox(i,j).getTaille().imag() );
    }
    entites[e].getVitesse().imag(0);
}


void Sort::finDeVie(const unsigned int e) {
    assert(!(e > entites.size()));
    entites.erase(getEntites().begin()+e);
}
