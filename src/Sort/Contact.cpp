#include "Contact.h"
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
 #define M_PI 3.1415926535
#endif

Contact::Contact() {
    degat = 20;
    recup = 500;
    temps = -recup;
}




void Contact::actualiseEntite(const complex<float> & pos) {
    if(entites.size() > 0) {
        entites[0].setPos(pos);
    }
}


bool Contact::lance(const complex<float> & pos) {
    if(tempsEcoule() - temps >= recup) {
        temps = tempsEcoule();
        if(entites.size() > 0)
            supprEntites(0);

        //Entite
            int dureeContact = -1;
            float graviteContact = 0;
            complex<float> positionContact(pos.real(),pos.imag());
            complex<float> tailleContact((2)*TBLOCK(), (1)*TBLOCK());
            complex<float> vitesseContact(0.000001,0.000001);
            complex<float> accelerContact(0,0);
            //Hitbox
                complex<float> positionHitboxContact(pos.real(),pos.imag());
                complex<float> tailleHitboxContact((2)*TBLOCK(), (1)*TBLOCK());
                int typeHitboxContact = 0;
            Hitbox hitboxContact(positionHitboxContact, tailleHitboxContact, typeHitboxContact);
            Entite entiteContact(temps, dureeContact, graviteContact, positionContact, tailleContact, vitesseContact, accelerContact, hitboxContact);
        addEntites(entiteContact);

        return true;
    }
    return false;
}


void Contact::aTouche(const unsigned int i) {
    Sort::aTouche(i);
    temps = tempsEcoule();
}
