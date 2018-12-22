#include "Hero.h"
#include "../Carte.h"

Hero::Hero() {
    vieMax = 200;
    vie = vieMax;
    saut = false;
    dSaut = true;
    regardeDroite = true;
    nage = false;
        int dureeHero = -1;
        float graviteHero = (1/64.)*TBLOCK();
        complex<float> positionHero(DIMX()/2,0);
        complex<float> tailleHero((7/8.)*TBLOCK(), (14/8.)*TBLOCK());
        complex<float> vitesseHero(0,0);
        complex<float> accelerHero(0,0);
            complex<float> positionHitboxHero(DIMX()/2,0);
            complex<float> tailleHitboxHero((7/8.)*TBLOCK(), (14/8.)*TBLOCK());
            int typeHitboxHero = 0;
        Hitbox hitboxHero(positionHitboxHero, tailleHitboxHero, typeHitboxHero);
    entite = Entite(0, dureeHero, graviteHero, positionHero, tailleHero, vitesseHero, accelerHero, hitboxHero);
    shurikenTroisCoups = new ShurikenTroisCoups;
    shurikenShotGun = new ShurikenShotGun;
    dashHero = new DashHero;
}

Hero::~Hero() {
    delete shurikenTroisCoups;
    shurikenTroisCoups = NULL;
    delete shurikenShotGun;
    shurikenShotGun = NULL;
    delete dashHero;
    dashHero = NULL;
}




void Hero::lanceShurikenTroisCoups(complex<float> cible) {
    if(shurikenTroisCoups->lance(complex<float>((entite.getPos().real()+(entite.getTaille().real()/2)-(1/8.)*TBLOCK()),(entite.getPos().imag()+(entite.getTaille().imag()/2)-(1/8.)*TBLOCK())), cible))
        shurikenShotGun->setTemps(tempsEcoule());
}

void Hero::actualiseEntiteShurikenTroisCoups(complex<float> cible) {
    shurikenTroisCoups->actualiseEntite(complex<float>((entite.getPos().real()+(entite.getTaille().real()/2)-(1/8.)*TBLOCK()),(entite.getPos().imag()+(entite.getTaille().imag()/2)-(1/8.)*TBLOCK())), cible);
}


const ShurikenTroisCoups * Hero::getShurikenTroisCoups() const {
    return shurikenTroisCoups;
}

ShurikenTroisCoups * Hero::getShurikenTroisCoups() {
    return shurikenTroisCoups;
}

void Hero::setShurikenTroisCoups(const ShurikenTroisCoups * s) {
    *shurikenTroisCoups = *s;
}




void Hero::lanceShurikenShotGun(complex<float> cible) {
    if(shurikenShotGun->lance(complex<float>((entite.getPos().real()+(entite.getTaille().real()/2)-(1/8.)*TBLOCK()),(entite.getPos().imag()+(entite.getTaille().imag()/2)-(1/8.)*TBLOCK())), cible))
        shurikenTroisCoups->setTemps(tempsEcoule());
}


const ShurikenShotGun * Hero::getShurikenShotGun() const {
    return shurikenShotGun;
}

ShurikenShotGun * Hero::getShurikenShotGun() {
    return shurikenShotGun;
}

void Hero::setShurikenShotGun(const ShurikenShotGun * s) {
    *shurikenShotGun = *s;
}




void Hero::lanceDashHero(complex<float> cible) {
    dashHero->lance(entite.getPos(), cible);
}

void Hero::actualiseEntiteDashHero() {
    dashHero->actualiseEntite(entite);
}


const DashHero * Hero::getDashHero() const {
    return dashHero;
}

DashHero * Hero::getDashHero() {
    return dashHero;
}

void Hero::setDashHero(const DashHero * s) {
    *dashHero = *s;
}

vector<Sort*> Hero::getSort() {
    vector<Sort*> sorts;
    sorts.push_back(getShurikenTroisCoups());
    sorts.push_back(getShurikenShotGun());
    sorts.push_back(getDashHero());
    return sorts;
}

const int Hero::getId() const {
    return 1;
}


void Hero::saute() {
    //Si le saut est dispo
    if(saut) {
        //Si le hero est dans l'eau
        if(nage) {
            entite.getVitesse().imag((-1/4.)*TBLOCK());
        } else {
            entite.getVitesse().imag((-1/3.)*TBLOCK());
        }
        saut = false;
    //Si le double saut est dispo et que l'on commence à retomber du premier saut
    } else if(dSaut && entite.getVitesse().imag() >= (-10/64.)*TBLOCK()) {
        //Si le hero est dans l'eau
        if(nage) {
            entite.getVitesse().imag((-1/4.)*TBLOCK());
        } else {
            entite.getVitesse().imag((-1/3.)*TBLOCK());
        }
        dSaut = false;
    }
}

void Hero::droite() {
    if(nage) {
        entite.getVitesse().real((1/16.)*TBLOCK());
    } else {
        entite.getVitesse().real((1/8.)*TBLOCK());
    }
    regardeDroite = true;
}

void Hero::gauche() {
    if(nage) {
        entite.getVitesse().real((-1/16.)*TBLOCK());
    } else {
        entite.getVitesse().real((-1/8.)*TBLOCK());
    }
    regardeDroite = false;
}

void Hero::attend() {
    entite.getVitesse().real(0);
}


void Hero::meurt() {
    vieMax = 200;
    vie = vieMax;
    saut = false;
    dSaut = true;
    regardeDroite = true;
        int dureeHero = -1;
        float graviteHero = (1/64.)*TBLOCK();
        complex<float> positionHero(DIMX()/2,0);
        complex<float> tailleHero((7/8.)*TBLOCK(), (14/8.)*TBLOCK());
        complex<float> vitesseHero(0,0);
        complex<float> accelerHero(0,0);
            complex<float> positionHitboxHero(DIMX()/2,0);
            complex<float> tailleHitboxHero((7/8.)*TBLOCK(), (14/8.)*TBLOCK());
            int typeHitboxHero = 0;
        Hitbox hitboxHero(positionHitboxHero, tailleHitboxHero, typeHitboxHero);
    entite = Entite(0, dureeHero, graviteHero, positionHero, tailleHero, vitesseHero, accelerHero, hitboxHero);
    delete shurikenTroisCoups;
    shurikenTroisCoups = NULL;
    delete shurikenShotGun;
    shurikenShotGun = NULL;
    delete dashHero;
    dashHero = NULL;
    shurikenTroisCoups = new ShurikenTroisCoups;
    shurikenShotGun = new ShurikenShotGun;
    dashHero = new DashHero;
}
