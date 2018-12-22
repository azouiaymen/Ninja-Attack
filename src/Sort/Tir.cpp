#include "Tir.h"
#include <math.h>
#include <stdlib.h>
#include <cassert>

#ifndef M_PI
 #define M_PI 3.1415926535
#endif

Tir::Tir() {
    degat = 10;
    recup = 500;
    temps = -recup;
}




bool Tir::lance(const complex<float> & pos, complex<float> cible) {
    if(tempsEcoule() - temps >= recup) {
        temps = tempsEcoule();
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
            int dureeTir = 2000;
            float graviteTir = 0;
            complex<float> positionTir = complex<float>(pos.real(),pos.imag());
            complex<float> tailleTir((2/8.)*TBLOCK(), (4/8.)*TBLOCK());
            complex<float> vitesseTir((10/64.)*TBLOCK()*cos(angle),(10/64.)*TBLOCK()*sin(angle));
            complex<float> accelerTir(0,0);
            //Hitbox
                complex<float> positionHitboxTir = complex<float>(pos.real(),pos.imag());
                complex<float> tailleHitboxTir((2/8.)*TBLOCK(), (4/8.)*TBLOCK());
                int typeHitboxTir = 0;
            Hitbox hitboxTir(positionHitboxTir, tailleHitboxTir, typeHitboxTir);
            Entite entiteTir(temps, dureeTir, graviteTir, positionTir, tailleTir, vitesseTir, accelerTir, hitboxTir);
        addEntites(entiteTir);
        return true;
    }
    return false;
}


const int Tir::getId() const {
    return 6;
}




void Tir::actualiseHitbox(const unsigned int e) {
    assert(!(e > entites.size()));
    entites[e].getHitbox().setPos(complex<float>(entites[e].getPos().real()+(1/16.)*TBLOCK(), entites[e].getPos().imag()+(1/16.)*TBLOCK()));
}


void Tir::colisionMurX(const unsigned int e, const int i, const int j, const Carte & carte) {
    assert(!(e > entites.size()));
    entites[e].setNe(-entites[e].getDuree());
}

void Tir::colisionMurY(const unsigned int e, const int i, const int j, const Carte & carte) {
    assert(!(e > entites.size()));
    entites[e].setNe(-entites[e].getDuree());
}
