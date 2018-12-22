#include "ShurikenShotGun.h"
#include <math.h>
#include <stdlib.h>
#include <cassert>

#ifndef M_PI
 #define M_PI 3.1415926535
#endif

ShurikenShotGun::ShurikenShotGun() {
    degat = 20;
    recup = 500;
    temps = -recup;
}




bool ShurikenShotGun::lance(const complex<float> & pos, complex<float> cible) {
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
            int dureeShuriken1 = 2000;
            float graviteShuriken1 = 0;
            complex<float> positionShuriken1(pos.real(),pos.imag());
            complex<float> tailleShuriken1((1/4.)*TBLOCK(),(1/4.)*TBLOCK());
            complex<float> vitesseShuriken1((2/4.)*TBLOCK()*cos(angle),(2/4.)*TBLOCK()*sin(angle));
            complex<float> accelerShuriken1(0, 0);
            //Hitbox
                complex<float> positionHitboxShuriken1(pos.real()+(1/16.)*TBLOCK(),pos.imag()+(1/16.)*TBLOCK());
                complex<float> tailleHitboxShuriken1((1/8.)*TBLOCK(),(1/8.)*TBLOCK());
                int typeHitboxShuriken1 = 0;
            Hitbox hitboxShuriken1(positionHitboxShuriken1, tailleHitboxShuriken1, typeHitboxShuriken1);
            Entite entiteShuriken1(temps, dureeShuriken1, graviteShuriken1, positionShuriken1, tailleShuriken1, vitesseShuriken1, accelerShuriken1, hitboxShuriken1);
        addEntites(entiteShuriken1);

        angle*=(180/M_PI);
        angle+=5;
        angle/=(180/M_PI);

        //Entite
            int dureeShuriken2 = 2000;
            float graviteShuriken2 = 0;
            complex<float> positionShuriken2(pos.real(),pos.imag());
            complex<float> tailleShuriken2((1/4.)*TBLOCK(),(1/4.)*TBLOCK());
            complex<float> vitesseShuriken2((2/4.)*TBLOCK()*cos(angle),(2/4.)*TBLOCK()*sin(angle));
            complex<float> accelerShuriken2(0, 0);
            //Hitbox
                complex<float> positionHitboxShuriken2(pos.real()+(1/16.)*TBLOCK(),pos.imag()+(1/16.)*TBLOCK());
                complex<float> tailleHitboxShuriken2((1/8.)*TBLOCK(),(1/8.)*TBLOCK());
                int typeHitboxShuriken2 = 0;
            Hitbox hitboxShuriken2(positionHitboxShuriken2, tailleHitboxShuriken2, typeHitboxShuriken2);
            Entite entiteShuriken2(temps, dureeShuriken2, graviteShuriken2, positionShuriken2, tailleShuriken2, vitesseShuriken2, accelerShuriken2, hitboxShuriken2);
        addEntites(entiteShuriken2);

        angle*=(180/M_PI);
        angle-=10;
        angle/=(180/M_PI);

        //Entite
            int dureeShuriken3 = 2000;
            float graviteShuriken3 = 0;
            complex<float> positionShuriken3(pos.real(),pos.imag());
            complex<float> tailleShuriken3((1/4.)*TBLOCK(),(1/4.)*TBLOCK());
            complex<float> vitesseShuriken3((2/4.)*TBLOCK()*cos(angle),(2/4.)*TBLOCK()*sin(angle));
            complex<float> accelerShuriken3(0,0);
            //Hitbox
                complex<float> positionHitboxShuriken3(pos.real()+(1/16.)*TBLOCK(),pos.imag()+(1/16.)*TBLOCK());
                complex<float> tailleHitboxShuriken3((1/8.)*TBLOCK(),(1/8.)*TBLOCK());
                int typeHitboxShuriken3 = 0;
            Hitbox hitboxShuriken3(positionHitboxShuriken3, tailleHitboxShuriken3, typeHitboxShuriken3);
            Entite entiteShuriken3(temps, dureeShuriken3, graviteShuriken3, positionShuriken3, tailleShuriken3, vitesseShuriken3, accelerShuriken3, hitboxShuriken3);
        addEntites(entiteShuriken3);
        return true;
    }
    return false;
}




void ShurikenShotGun::actualiseHitbox(const unsigned int e) {
    assert(!(e > entites.size()));
    entites[e].getHitbox().setPos(complex<float>(entites[e].getPos().real()+(1/16.)*TBLOCK(), entites[e].getPos().imag()+(1/16.)*TBLOCK()));
}


void ShurikenShotGun::colisionMurX(const unsigned int e, const int i, const int j, const Carte & carte) {
    assert(!(e > entites.size()));
    if(entites[e].getVitesse().real() > 0) {
        entites[e].getPos().real( carte.getHitbox(i,j).getPos().real() - entites[e].getHitbox().getTaille().real() );
    } else if(entites[e].getVitesse().real() < 0) {
        entites[e].getPos().real( carte.getHitbox(i,j).getPos().real() + carte.getHitbox(i,j).getTaille().real() - entites[e].getHitbox().getTaille().real() );
    }
    entites[e].setVitesse(complex<float>(0,0));
    entites[e].setAcceler(complex<float>(0,0));
}

void ShurikenShotGun::colisionMurY(const unsigned int e, const int i, const int j, const Carte & carte) {
    assert(!(e > entites.size()));
    if(entites[e].getVitesse().imag() > 0) {
        entites[e].getPos().imag( carte.getHitbox(i,j).getPos().imag() - entites[e].getHitbox().getTaille().imag() );
    } else if(entites[e].getVitesse().imag() < 0) {
        entites[e].getPos().imag( carte.getHitbox(i,j).getPos().imag() + carte.getHitbox(i,j).getTaille().imag() - entites[e].getHitbox().getTaille().imag() );
    }
    entites[e].setVitesse(complex<float>(0,0));
    entites[e].setAcceler(complex<float>(0,0));
}


const int ShurikenShotGun::getId() const {
    return 2;
}
