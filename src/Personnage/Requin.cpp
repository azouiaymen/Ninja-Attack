#include "Requin.h"
#include "../Carte.h"

Requin::Requin() {
    vieMax = 100;
    vie = vieMax;
    saut = false;
    dSaut = false;
    regardeDroite = true;
    nage = false;
        int dureeRequin = -1;
        float graviteRequin = 0.2;
        complex<float> positionRequin = complex<float>(0,0);//zoneSpawn;
        complex<float> tailleRequin((2)*TBLOCK(), (1)*TBLOCK());
        complex<float> vitesseRequin(0,0);
        complex<float> accelerRequin(0,0);
            complex<float> positionHitboxRequin = complex<float>(0,0);//zoneSpawn;
            complex<float> tailleHitboxRequin((2)*TBLOCK(), (1)*TBLOCK());
            int typeHitboxRequin = 0;
        Hitbox hitboxRequin(positionHitboxRequin, tailleHitboxRequin, typeHitboxRequin);
    entite = Entite(0, dureeRequin, graviteRequin, positionRequin, tailleRequin, vitesseRequin, accelerRequin, hitboxRequin);
    dash = new Dash;
}

Requin::Requin(const complex<float> & pos) {
    vieMax = 100;
    vie = vieMax;
    saut = false;
    dSaut = false;
    regardeDroite = true;
    nage = false;
        int dureeRequin = -1;
        float graviteRequin = 0.2;
        complex<float> positionRequin = pos;
        complex<float> tailleRequin((2)*TBLOCK(), (1)*TBLOCK());
        complex<float> vitesseRequin(0,0);
        complex<float> accelerRequin(0,0);
            complex<float> positionHitboxRequin = pos;
            complex<float> tailleHitboxRequin((2)*TBLOCK(), (1)*TBLOCK());
            int typeHitboxRequin = 0;
        Hitbox hitboxRequin(positionHitboxRequin, tailleHitboxRequin, typeHitboxRequin);
    entite = Entite(0, dureeRequin, graviteRequin, positionRequin, tailleRequin, vitesseRequin, accelerRequin, hitboxRequin);
    dash = new Dash;
}

Requin::~Requin() {
    delete dash;
    dash = NULL;
}




void Requin::lanceDash(complex<float> cible) {
    dash->lance(complex<float>(entite.getPos().real()+entite.getTaille().real()/2,entite.getPos().imag()), cible);
}

void Requin::actualiseEntiteDash() {
    dash->actualiseEntite(entite);
}


const Dash * Requin::getDash() const {
    return dash;
}

Dash * Requin::getDash() {
    return dash;
}

void Requin::setDash(const Dash * s) {
    *dash = *s;
}




void Requin::reflechis(const Entite & hero, const Carte & carte) {
    nage = false;

    //Permet de definir si le requin nage, on verifie si la tuile derniere le requin existe et si elle est de type 2
    if((int)((entite.getPos().real()+(entite.getTaille().real()/2))/TBLOCK()) < carte.getDim().real()
        && (int)((entite.getPos().real()+(entite.getTaille().real()/2))/TBLOCK()) >= 0
        && (int)(entite.getPos().imag()/TBLOCK()) < carte.getDim().imag()
        && (int)(entite.getPos().imag()/TBLOCK()) >= 0)
    {
        if(carte.getHitbox((int)((entite.getPos().real()+(entite.getTaille().real()/2))/TBLOCK()), (int)(entite.getPos().imag()/TBLOCK())).getType() == 2) {
            nage = true;
        }
    }

    //Si le requin est sous le personnage il flote sinon il coule
    if(entite.getPos().imag()+entite.getTaille().imag() <= hero.getPos().imag() && entite.getGravite() < 0) {
        entite.setVitesse(complex<float>(0,0));
        entite.setGravite(entite.getGravite() *-1);
    } else if(entite.getPos().imag() >= hero.getPos().imag()+hero.getTaille().imag() && entite.getGravite() > 0 && nage) {
        entite.setVitesse(complex<float>(0,0));
        entite.setGravite(entite.getGravite() *-1);
    }
    if(!nage && entite.getGravite() < 0) {
        if(entite.getVitesse().imag() < -5)
            entite.setVitesse(complex<float>(entite.getVitesse().real(), -5));
        entite.setGravite(entite.getGravite() *-1);
    }

    //Si le requin est à moins de 500 pixel du hero, le requin va vers le hero
    if((abs(hero.getPos().real() - entite.getPos().real()) < 500) || (abs((hero.getPos().real()+hero.getTaille().real()) - (entite.getPos().real()+entite.getTaille().real())) < 500)) {
        if(hero.getPos().real()+hero.getTaille().real() > entite.getPos().real() && hero.getPos().real()+hero.getTaille().real() > (entite.getPos().real() + entite.getTaille().real())) {
            droite();
        } else if(hero.getPos().real() < entite.getPos().real() && hero.getPos().real() < (entite.getPos().real()+entite.getTaille().real())) {
            gauche();
        } else {
            attend();
        }
    }

    //Si le requin est à moins de 500 pixel le requin tente de lancer son dash sur le hero
    if(abs(hero.getPos().real() - entite.getPos().real()) < 500 || abs((hero.getPos().real()+hero.getTaille().real()) - (entite.getPos().real()+entite.getTaille().real())) < 500) {
        lanceDash(complex<float>(hero.getPos().real()+hero.getTaille().real()/2, hero.getPos().imag()+hero.getTaille().imag()/2));
    }
}

void Requin::droite() {
    if(!nage) {
        entite.getVitesse().real((1/30.)*TBLOCK());
    } else {
        entite.getVitesse().real((1/10.)*TBLOCK());
    }
    regardeDroite = true;
}

void Requin::gauche() {
    if(!nage) {
        entite.getVitesse().real((-1/30.)*TBLOCK());
    } else {
        entite.getVitesse().real((-1/10.)*TBLOCK());
    }
    regardeDroite = false;
}




vector<Sort*> Requin::getSort() {
    vector<Sort*> sorts;
    sorts.push_back(getDash());
    return sorts;
}

const int Requin::getId() const {
    return 3;
}
