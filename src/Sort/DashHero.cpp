#include "DashHero.h"
#include <math.h>
#include <stdlib.h>
#include <cassert>

#ifndef M_PI
 #define M_PI 3.1415926535
#endif

DashHero::DashHero() {
    degat = 50;
    recup = 2000;
    temps = -recup;
}




void DashHero::actualiseEntite(Entite & e) {
    if(entites.size() > 0) {
        e.getPos().real(entites[0].getPos().real());
        e.getPos().imag(entites[0].getPos().imag());
        e.setVitesse(complex<float>(0,0));
        e.setAcceler(complex<float>(0,0));
    }
}


bool DashHero::lance(const complex<float> & pos, complex<float> cible) {
    if(tempsEcoule() - temps >= recup && entites.size() == 0) {
        temps = tempsEcoule();
        degat = 50;
        //Angle
            float adjacent = pos.real()-cible.real();
            float hypotenuse = sqrt((pos.real()-cible.real())*(pos.real()-cible.real())+(pos.imag()-cible.imag())*(pos.imag()-cible.imag()));
            float angle = acos(adjacent/hypotenuse);
            if((pos.imag() - cible.imag()) < 0)
                angle = -angle;
            angle*=(180/M_PI);
            angle+=180;
            if(angle >= 360)
                angle = 0;
            angle/=(180/M_PI);
        //Entite
            int dureeDash = 250;
            float graviteDash = 0;
            complex<float> positionDash(pos.real(),pos.imag());
            complex<float> tailleDash((7/8.)*TBLOCK(), (14/8.)*TBLOCK());
            complex<float> vitesseDash((40/64.)*TBLOCK()*cos(angle),(40/64.)*TBLOCK()*sin(angle));
            complex<float> accelerDash(0,0);
            //Hitbox
                complex<float> positionHitboxDash(pos.real(),pos.imag());
                complex<float> tailleHitboxDash((7/8.)*TBLOCK(), (14/8.)*TBLOCK());
                int typeHitboxDash = 0;
            Hitbox hitboxDash(positionHitboxDash, tailleHitboxDash, typeHitboxDash);
            Entite entiteDash(temps, dureeDash, graviteDash, positionDash, tailleDash, vitesseDash, accelerDash, hitboxDash);
        addEntites(entiteDash);
        return true;
    }
    return false;
}


void DashHero::aTouche(const unsigned int i) {
    assert(!(i > entites.size()));
    degat = 0;
}


const int DashHero::getId() const {
    return 3;
}
