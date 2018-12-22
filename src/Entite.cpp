#include "Entite.h"
#include <time.h>
#include <iostream>
using namespace std;

Entite::Entite() {
    ne = (1000*(((float)clock())/CLOCKS_PER_SEC));
    duree = -1;
    gravite = 0;
    pos = complex<int>(-200,-200);
    taille = complex<int>(0,0);
    vitesse = complex<int>(0,0);
    acceler = complex<int>(0,0);
    hitbox.setPos(pos);
    hitbox.setTaille(taille);
    hitbox.setType(-1);
}

Entite::Entite(const int n, const int d, const float g, const complex<float> p, const complex<float> ta, const complex<float> v, const complex<float> a, const Hitbox & h) {
    ne = n;
    duree = d;
    gravite = g;
    pos = p;
    taille = ta;
    vitesse = v;
    acceler = a;
    hitbox = h;
}

Entite::Entite(const Entite & e) {
    ne = e.getNe();
    duree = e.getDuree();
    gravite = e.getGravite();
    pos = e.getPos();
    vitesse = e.getVitesse();
    acceler = e.getAcceler();
    taille = e.getTaille();
    hitbox = e.getHitbox();
}




const int Entite::getNe() const {
    return ne;
}

void Entite::setNe(const int n)  {
    ne = n;
}


const int Entite::getDuree() const {
    return duree;
}

void Entite::setDuree(const int d)  {
    duree = d;
}

const float Entite::getItUnit() const {
    return itUnit;
}

void Entite::setItUnit(const float i) {
    itUnit = i;
}


const float Entite::getGravite() const {
    return gravite;
}

void Entite::setGravite(const float g)  {
    gravite = g;
}


const complex<float> & Entite::getPos()const {
    return pos;
}

complex<float> & Entite::getPos() {
    return pos;
}

void Entite::setPos(const complex<float> &cplx) {
    pos = cplx;
}


const complex<float> & Entite::getVitesse()const {
    return vitesse;
}

complex<float> & Entite::getVitesse() {
    return vitesse;
}

void Entite::setVitesse(const complex<float> &cplx) {
    vitesse = cplx;
}


const complex<float> & Entite::getAcceler()const {
    return acceler;
}

complex<float> & Entite::getAcceler() {
    return acceler;
}

void Entite::setAcceler(const complex<float> &cplx) {
    acceler = cplx;
}


const complex<float> & Entite::getTaille()const {
    return taille;
}

complex<float> & Entite::getTaille() {
    return taille;
}

void Entite::setTaille(const complex<float> &cplx) {
    taille = cplx;
}


const Hitbox & Entite::getHitbox() const {
    return hitbox;
}

Hitbox & Entite::getHitbox() {
    return hitbox;
}

void Entite::setHitbox(const Hitbox & e) {
    hitbox = e;
}




void Entite::actualiseVitesse() {
    vitesse.real(vitesse.real() + acceler.real());
    vitesse.imag(vitesse.imag() + acceler.imag() + gravite);
}

void Entite::actualiseUnitPosX() {
    float vitesseUnitX;
    if(getNbUnit() == 0) {
        vitesseUnitX = 0;
    } else {
        vitesseUnitX = vitesse.real()/getNbUnit();
    }
    pos.real(pos.real() + vitesseUnitX);
}

void Entite::actualiseUnitPosY() {
    float vitesseUnitY;
    if(getNbUnit() == 0) {
        vitesseUnitY = 0;
    } else {
        vitesseUnitY = vitesse.imag()/getNbUnit();
    }
    pos.imag(pos.imag() + vitesseUnitY);
}

const float Entite::getNbUnit() const {
    //On cherche le max de la valeur absolue de chaque dimention de la vitesse (x,y), si on est entre 0 et 1 on considere que c'est 1
    if(max(abs(vitesse.real()), abs(vitesse.imag())) < 1 && max(abs(vitesse.real()), abs(vitesse.imag())) > 0)
        return 1;
    return max(abs(vitesse.real()), abs(vitesse.imag()));
}
