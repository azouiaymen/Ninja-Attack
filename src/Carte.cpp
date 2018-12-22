#include "Carte.h"
#include <fstream>
#include <cassert>

using namespace std;

Carte::Carte() {}

Carte::Carte(const string nomFichier) {
    ifstream fichier (nomFichier.c_str());
    assert(fichier.is_open());

    int x,y;
    fichier >> x;
    fichier >> y;

    dim.real(x);
    dim.imag(y);

    texture.resize(x, vector<char>(y));
    hitbox.resize(x, vector<Hitbox>(y));

    string listeDur;
    string listeMou;
    fichier >> listeDur >> listeMou;

    char lettre;
    for(int j = 0; j < y; j++) {
        for(int i = 0; i < x; i++) {
            fichier >> lettre;
            texture[i][j] = lettre;
            hitbox[i][j].setType(0);
            hitbox[i][j].setPos(complex<float>(i*TBLOCK(),j*TBLOCK()));
            hitbox[i][j].setTaille(complex<float>(TBLOCK(),TBLOCK()));
            if(listeDur.find_first_of(lettre) != string::npos)
                hitbox[i][j].setType(1);
            if(listeMou.find_first_of(lettre) != string::npos)
                hitbox[i][j].setType(2);
        }
    }
    fichier.close();
}




const complex<int> Carte::getDim() const {
    return dim;
}


const char & Carte::getTexture(const unsigned int x, const unsigned int y) const {
    assert(x < texture.size() && y < texture[x].size());
    return texture[x][y];
}


const Hitbox & Carte::getHitbox(const unsigned int x, const unsigned int y) const {
    assert(x < hitbox.size() && y < hitbox[x].size());
    return hitbox[x][y];
}
