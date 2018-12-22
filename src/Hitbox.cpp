#include "Hitbox.h"
#include <math.h>

Hitbox::Hitbox() {
    pos = complex<float>(-200,-200);
    taille = complex<float>(0,0);
    type = -1;
}

Hitbox::Hitbox(const complex<float> p, const complex<float> ta, const int ty) {
    pos = p;
    taille = ta;
    type = ty;
}




const int Hitbox::getType() const {
    return type;
}

void Hitbox::setType(const int tpe) {
    type = tpe;
}


const complex<float> & Hitbox::getPos() const {
    return pos;
}

complex<float> & Hitbox::getPos() {
    return pos;
}

void Hitbox::setPos(const complex<float> &cplx) {
    pos = cplx;
}


const complex<float> & Hitbox::getTaille() const {
    return taille;
}

complex<float> & Hitbox::getTaille() {
    return taille;
}

void Hitbox::setTaille(const complex<float> &cplx) {
    taille = cplx;
}



bool Hitbox::touche(const Hitbox& hitb) const {
    if(((max((pos.real()+(taille.real()-1)), (hitb.getPos().real()+(hitb.getTaille().real()-1))) - min(pos.real(), hitb.getPos().real())) < ((taille.real() + hitb.getTaille().real())-1)) &&
       ((max((pos.imag()+(taille.imag()-1)), (hitb.getPos().imag()+(hitb.getTaille().imag()-1))) - min(pos.imag(), hitb.getPos().imag())) < ((taille.imag() + hitb.getTaille().imag())-1))) {
        return true;
    }
    return false;
}
