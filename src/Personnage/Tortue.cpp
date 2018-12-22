#include "Tortue.h"
#include "../Carte.h"

Tortue::Tortue() {
    vieMax = 100;
    vie = vieMax;
    saut = false;
    dSaut = false;
    regardeDroite = true;
    nage = false;
        int dureeTortue = -1;
        float graviteTortue = 2;
        complex<float> positionTortue = complex<float>(0,0);//zoneSpawn;
        complex<float> tailleTortue((2)*TBLOCK(), (1)*TBLOCK());
        complex<float> vitesseTortue(0,0);
        complex<float> accelerTortue(0,0);
            complex<float> positionHitboxTortue = complex<float>(0,0);//zoneSpawn;
            complex<float> tailleHitboxTortue((2)*TBLOCK(), (1)*TBLOCK());
            int typeHitboxTortue = 0;
        Hitbox hitboxTortue(positionHitboxTortue, tailleHitboxTortue, typeHitboxTortue);
    entite = Entite(0, dureeTortue, graviteTortue, positionTortue, tailleTortue, vitesseTortue, accelerTortue, hitboxTortue);
    contact = new Contact;
}

Tortue::~Tortue() {
    delete contact;
    contact = NULL;
}

Tortue::Tortue(const complex<float> & pos) {
    vieMax = 100;
    vie = vieMax;
    saut = false;
    dSaut = false;
    regardeDroite = true;
    nage = false;
        int dureeTortue = -1;
        float graviteTortue = 1;
        complex<float> positionTortue = pos;
        complex<float> tailleTortue((2)*TBLOCK(), (1)*TBLOCK());
        complex<float> vitesseTortue(0,0);
        complex<float> accelerTortue(0,0);
            complex<float> positionHitboxTortue = pos;
            complex<float> tailleHitboxTortue((2)*TBLOCK(), (1)*TBLOCK());
            int typeHitboxTortue = 0;
        Hitbox hitboxTortue(positionHitboxTortue, tailleHitboxTortue, typeHitboxTortue);
    entite = Entite(0, dureeTortue, graviteTortue, positionTortue, tailleTortue, vitesseTortue, accelerTortue, hitboxTortue);
    contact = new Contact;
}




const Contact * Tortue::getContact() const {
    return contact;
}

Contact * Tortue::getContact() {
    return contact;
}

void Tortue::setContact(const Contact * s) {
    *contact = *s;
}




void Tortue::lanceContact() {
    contact->lance(entite.getPos());
}

void Tortue::actualiseEntiteContact() {
    contact->actualiseEntite(entite.getPos());
}





void Tortue::reflechis(const Entite & hero, const Carte & carte) {
    //Si la tortue est à moins de 500 pixel du hero
    if(abs(hero.getPos().real() - entite.getPos().real()) < 500 || abs((hero.getPos().real()+hero.getTaille().real()) - (entite.getPos().real()+entite.getTaille().real())) < 500) {
        //Selon si elle doit aller à droite ou à gauche pour se rapprocher
        if(hero.getPos().real()+hero.getTaille().real() > entite.getPos().real() && hero.getPos().real()+hero.getTaille().real() > (entite.getPos().real() + entite.getTaille().real())) {
            //Et si la tuile sous ses pieds existe et qu'elle ne risque pas de tomber dans le vide
            if(((int)(entite.getPos().real()+entite.getTaille().real())/TBLOCK()) < carte.getDim().real()
                && ((int)(entite.getPos().real()+entite.getTaille().real())/TBLOCK()) >= 0
                && ((int)(entite.getPos().imag()+entite.getTaille().imag())/TBLOCK()) < carte.getDim().imag()
                && ((int)(entite.getPos().imag()+entite.getTaille().imag())/TBLOCK()) >= 0)
            {
                if(carte.getHitbox(((int)(entite.getPos().real()+entite.getTaille().real())/TBLOCK()), ((int)(entite.getPos().imag()+entite.getTaille().imag())/TBLOCK())).getType() == 1) {
                    droite();
                } else {
                    attend();
                }
            }
        } else if(hero.getPos().real() < entite.getPos().real() && hero.getPos().real() < (entite.getPos().real()+entite.getTaille().real())) {
            //Et si la tuile sous ses pieds existe et qu'elle ne risque pas de tomber dans le vide
            if(((int)entite.getPos().real()/TBLOCK()) < carte.getDim().real()
                && ((int)entite.getPos().real()/TBLOCK()) >= 0
                && ((int)(entite.getPos().imag()+entite.getTaille().imag())/TBLOCK()) < carte.getDim().imag()
                && ((int)(entite.getPos().imag()+entite.getTaille().imag())/TBLOCK()) >= 0)
            {
                if(carte.getHitbox(((int)entite.getPos().real()/TBLOCK()), ((int)(entite.getPos().imag()+entite.getTaille().imag())/TBLOCK())).getType() == 1) {
                    gauche();
                } else {
                    attend();
                }
            }
        } else {
            attend();
        }
    } else {
        attend();
    }
    lanceContact();
}




void Tortue::saute() {
    if(saut) {
        entite.getVitesse().imag((-3/16.)*TBLOCK());
        saut = !saut;
    }
}

void Tortue::droite() {
    entite.getVitesse().real((1/10.)*TBLOCK());
    regardeDroite = true;
}

void Tortue::gauche() {
    entite.getVitesse().real((-1/10.)*TBLOCK());
    regardeDroite = false;
}

vector<Sort*> Tortue::getSort() {
    vector<Sort*> sorts;
    sorts.push_back(getContact());
    return sorts;
}

const int Tortue::getId() const {
    return 2;
}
