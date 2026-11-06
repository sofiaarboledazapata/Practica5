#include <iostream>
#include "particula.h"

using namespace std;

int main()
{
    Particula p1(100, 200, 5, 3, 2, 10);

    cout << "Posicion X: " << p1.getX() << endl;
    cout << "Posicion Y: " << p1.getY() << endl;
    cout << "Velocidad X: " << p1.getVx() << endl;
    cout << "Velocidad Y: " << p1.getVy() << endl;
    cout << "Masa: " << p1.getMasa() << endl;
    cout << "Radio: " << p1.getRadio() << endl;


    cout << "\nMoviendo la particula..." << endl;

    p1.mover(0.5);

    cout << "Nueva posicion X: " << p1.getX() << endl;
    cout << "Nueva posicion Y: " << p1.getY() << endl;


    cout << "\nCambiando la velocidad..." << endl;

    p1.setVelocidad(-5, 3);

    cout << "Nueva velocidad X: " << p1.getVx() << endl;
    cout << "Nueva velocidad Y: " << p1.getVy() << endl;

    p1.mover(1.0);

    cout << "Posicion X: " << p1.getX() << endl;
    cout << "Posicion Y: " << p1.getY() << endl;

    return 0;
}

