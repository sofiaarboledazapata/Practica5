
#include <iostream>
#include "particula.h"
#include "caja.h"
#include "obstaculo.h"
#include "simulacion.h"

using namespace std;

int main()
{
    // Crear la caja
    Caja escenario(800, 500);

    // Crear las cuatro particulas
    Particula p1(100, 175, 100, 0, 2, 10);
    Particula p2(785, 450, 80, 0, 3, 12);
    Particula p3(300, 400, 50, 0, 1.5, 8);
    Particula p4(350, 400, -50, 0, 2.5, 10);


    // Crear los cuatro obstaculos
    Obstaculo o1(200, 150, 50);
    Obstaculo o2(450, 100, 60);
    Obstaculo o3(150, 350, 40);
    Obstaculo o4(500, 300, 50);

    // Crear la simulacion
    Simulacion simulacion(escenario, 0.02);

    // Agregar las particulas
    simulacion.agregarParticula(p1);
    simulacion.agregarParticula(p2);
    simulacion.agregarParticula(p3);
    simulacion.agregarParticula(p4);

    // Agregar los obstaculos
    simulacion.agregarObstaculo(o1);
    simulacion.agregarObstaculo(o2);
    simulacion.agregarObstaculo(o3);
    simulacion.agregarObstaculo(o4);

    cout << "Simulacion creada correctamente." << endl;

    cout << "Cantidad inicial de particulas: "
         << simulacion.getCantidadParticulas() << endl;

    cout << "Cantidad de obstaculos: "
         << simulacion.getCantidadObstaculos() << endl;

    cout << "\nPosiciones iniciales:" << endl;
    simulacion.mostrarPosiciones();


    simulacion.ejecutar(100);

    cout << "\nCantidad final de particulas: "
         << simulacion.getCantidadParticulas() << endl;


    return 0;
}
