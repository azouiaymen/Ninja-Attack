#include "Aigle.h"
#include "../Carte.h"

Aigle::Aigle() {
    vieMax = 100;
    vie = vieMax;
    saut = false;
    dSaut = false;
    regardeDroite = true;
    nage = false;
        int dureeAigle = -1;
        float graviteAigle = 0.1;
        complex<float> positionAigle = complex<float>(0,0);//zoneSpawn;
        complex<float> tailleAigle((2)*TBLOCK(), (2)*TBLOCK());
        complex<float> vitesseAigle(0,0);
        complex<float> accelerAigle(0,0);
            complex<float> positionHitboxAigle = complex<float>(0,0);//zoneSpawn;
            complex<float> tailleHitboxAigle((2)*TBLOCK(), (2)*TBLOCK());
            int typeHitboxAigle = 0;
        Hitbox hitboxAigle(positionHitboxAigle, tailleHitboxAigle, typeHitboxAigle);
    entite = Entite(0, dureeAigle, graviteAigle, positionAigle, tailleAigle, vitesseAigle, accelerAigle, hitboxAigle);
    tir = new Tir;
}

Aigle::Aigle(const complex<float> & pos) {
    vieMax = 100;
    vie = vieMax;
    saut = false;
    dSaut = false;
    regardeDroite = true;
    nage = false;
        int dureeAigle = -1;
        float graviteAigle = 0.1;
        complex<float> positionAigle = pos;
        complex<float> tailleAigle((2)*TBLOCK(), (2)*TBLOCK());
        complex<float> vitesseAigle(0,0);
        complex<float> accelerAigle(0,0);
            complex<float> positionHitboxAigle = pos;
            complex<float> tailleHitboxAigle((2)*TBLOCK(), (2)*TBLOCK());
            int typeHitboxAigle = 0;
        Hitbox hitboxAigle(positionHitboxAigle, tailleHitboxAigle, typeHitboxAigle);
    entite = Entite(0, dureeAigle, graviteAigle, positionAigle, tailleAigle, vitesseAigle, accelerAigle, hitboxAigle);
    tir = new Tir;
}

Aigle::~Aigle() {
    delete tir;
    tir = NULL;
}




void Aigle::lanceTir(complex<float> cible) {
    tir->lance(complex<float>(entite.getPos().real()+(entite.getTaille().real()/2),entite.getPos().imag()+(entite.getTaille().imag()/2)), cible);
}


const Tir * Aigle::getTir() const {
    return tir;
}

Tir * Aigle::getTir() {
    return tir;
}

void Aigle::setTir(const Tir * s) {
    *tir = *s;
}


void Aigle::reflechis(const Entite & hero, const Carte & carte) {
    //Si les pieds de l'aigle touche la hauteur de la tête du hero, l'aigle récupere son saut
    if(entite.getPos().imag()+entite.getTaille().imag() >= hero.getPos().imag()) {
        saut = true;
    }
    //L'aigle tente toujours de sauter
    saute();

    //Si le hero est entre 300 et 500 pixel de distance de l'aigle, alors l'aigle vol dans sa direction
    if((abs(hero.getPos().real() - entite.getPos().real()) < 500 && abs(hero.getPos().real() - entite.getPos().real()) > 300) || (abs((hero.getPos().real()+hero.getTaille().real()) - (entite.getPos().real()+entite.getTaille().real())) < 500 && abs((hero.getPos().real()+hero.getTaille().real()) - (entite.getPos().real()+entite.getTaille().real())) > 300)) {
        if(hero.getPos().real()+hero.getTaille().real() > entite.getPos().real() && hero.getPos().real()+hero.getTaille().real() > (entite.getPos().real() + entite.getTaille().real())) {
            droite();
        } else if(hero.getPos().real() < entite.getPos().real() && hero.getPos().real() < (entite.getPos().real()+entite.getTaille().real())) {
            gauche();
        } else {
            attend();
        }
    }

    //Si le hero est à moins de 500 pixel de distance l'aigle lui tir dessus
    if(abs(hero.getPos().real() - entite.getPos().real()) < 500 || abs((hero.getPos().real()+hero.getTaille().real()) - (entite.getPos().real()+entite.getTaille().real())) < 500) {
        lanceTir(complex<float>(hero.getPos().real()+hero.getTaille().real()/2, hero.getPos().imag()+hero.getTaille().imag()/2));
    }
}


void Aigle::saute() {
    if(saut) {
        entite.getVitesse().imag((-6/64.)*TBLOCK());
        saut = false;
    }
}

void Aigle::droite() {
    entite.getVitesse().real((1/10.)*TBLOCK());
    regardeDroite = true;
}

void Aigle::gauche() {
    entite.getVitesse().real((-1/10.)*TBLOCK());
    regardeDroite = false;
}


vector<Sort*> Aigle::getSort() {
    vector<Sort*> sorts;
    sorts.push_back(getTir());
    return sorts;
}

const int Aigle::getId() const {
    return 4;
}

