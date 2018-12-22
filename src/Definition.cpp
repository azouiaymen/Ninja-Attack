#include "Definition.h"
#include <iostream>
using namespace std;

const int DIMX() {
    return (1024);
}

const int DIMY() {
    return (DIMX()*9/16);
}

const int TBLOCK() {
    return (DIMX()/32);
}

const float tempsEcoule() {
    return 0.001*std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - START).count();
}
