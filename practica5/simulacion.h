#ifndef SIMULACION_H
#define SIMULACION_H

#include <vector>
#include <string>
#include "particula.h"
#include "obstaculo.h"
#include "caja.h"

class Simulacion
{
private:
    Caja caja;
    std::vector<Particula> particulas;
    std::vector<Obstaculo> obstaculos;

    double tiempoActual;
    double dt;


    void verificarColisionPared(Particula& p);
    bool hayColisionObstaculo(const Particula& p,
                              const Obstaculo& o) const;


    void resolverColisionObstaculo(Particula& p,
                                   const Obstaculo& o);


    bool hayColisionParticulas(const Particula& p1,
                               const Particula& p2) const;


    Particula fusionarParticulas(const Particula& p1,
                                 const Particula& p2) const;

    std::vector<std::string> eventosColisiones;

    int siguienteId;


public:
    Simulacion(const Caja& caja, double dt);

    void agregarParticula(const Particula& particula);
    void agregarObstaculo(const Obstaculo& obstaculo);

    int getCantidadParticulas() const;
    int getCantidadObstaculos() const;

    void avanzarPaso();

    void ejecutar(int cantidadPasos);


    void mostrarPosiciones() const;



};

#endif // SIMULACION_H
