#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "simulacion.h"


Simulacion::Simulacion(const Caja& caja, double dt)
    : caja(caja), tiempoActual(0.0), dt(dt), siguienteId(1)
{
}


void Simulacion::agregarParticula(const Particula& particula)
{
    Particula copia = particula;

    copia.setId(siguienteId);
    siguienteId++;

    particulas.push_back(copia);
}


void Simulacion::agregarObstaculo(const Obstaculo& obstaculo)
{
    obstaculos.push_back(obstaculo);
}

int Simulacion::getCantidadParticulas() const
{
    return particulas.size();
}

int Simulacion::getCantidadObstaculos() const
{
    return obstaculos.size();
}



void Simulacion::avanzarPaso()
{
    int numeroParticula = 1;

    for (Particula& p : particulas)
    {
        p.mover(dt);
        verificarColisionPared(p);

        int numeroObstaculo = 1;

        for (const Obstaculo& o : obstaculos)
        {

            if (hayColisionObstaculo(p, o))
            {
                resolverColisionObstaculo(p, o);

                std::cout << "Colision detectada entre particula "
                          << numeroParticula
                          << " y obstaculo "
                          << numeroObstaculo << std::endl;

                // Registrar la colision
                eventosColisiones.push_back(
                    std::to_string(tiempoActual + dt) + ",Obstaculo,"
                    + std::to_string(p.getId()) + ","
                    + std::to_string(numeroObstaculo)
                    );

            }


            numeroObstaculo++;
        }

        numeroParticula++;
    }

    // Verificar colisiones entre particulas
    int total = getCantidadParticulas();
    bool fusionRealizada = false;

    for (int i = 0; i < total && !fusionRealizada; i++)
    {
        for (int j = i + 1; j < total; j++)
        {
            if (hayColisionParticulas(particulas[i], particulas[j]))
            {
                // Guardar los identificadores originales
                int id1 = particulas[i].getId();
                int id2 = particulas[j].getId();

                // Crear la particula fusionada
                Particula nueva = fusionarParticulas(
                    particulas[i], particulas[j]);

                // Asignar un identificador nuevo
                nueva.setId(siguienteId);
                siguienteId++;

                // Reemplazar las particulas originales
                particulas[i] = nueva;
                particulas.erase(particulas.begin() + j);

                std::cout << "Se fusionaron las particulas "
                          << id1 << " y " << id2
                          << ". Nueva particula: "
                          << nueva.getId() << std::endl;

                // Registrar la fusion
                eventosColisiones.push_back(
                    std::to_string(tiempoActual + dt) + ",Fusion,"
                    + std::to_string(id1) + ","
                    + std::to_string(id2)
                    );

                fusionRealizada = true;
                break;
            }

        }
    }

    tiempoActual += dt;
}



void Simulacion::mostrarPosiciones() const
{
    for (const Particula& p : particulas)
    {
        std::cout << "Particula " << p.getId()
        << ": (" << p.getX()
        << ", " << p.getY() << ")"
        << " | Velocidad: (" << p.getVx()
        << ", " << p.getVy() << ")"
        << std::endl;
    }
}


void Simulacion::verificarColisionPared(Particula& p)
{
    double x = p.getX();
    double y = p.getY();
    double vx = p.getVx();
    double vy = p.getVy();
    double radio = p.getRadio();

    std::string paredX = "";
    std::string paredY = "";

    // Pared izquierda
    if (x - radio < 0)
    {
        x = radio;
        vx = -vx;
        paredX = "Izquierda";
    }
    // Pared derecha
    else if (x + radio > caja.getAncho())
    {
        x = caja.getAncho() - radio;
        vx = -vx;
        paredX = "Derecha";
    }

    // Pared superior
    if (y - radio < 0)
    {
        y = radio;
        vy = -vy;
        paredY = "Superior";
    }
    // Pared inferior
    else if (y + radio > caja.getAlto())
    {
        y = caja.getAlto() - radio;
        vy = -vy;
        paredY = "Inferior";
    }

    // Actualizar la particula
    p.setPosicion(x, y);
    p.setVelocidad(vx, vy);

    // Registrar colision horizontal
    if (!paredX.empty())
    {
        eventosColisiones.push_back(
            std::to_string(tiempoActual + dt) + ",Pared,"
            + std::to_string(p.getId()) + "," + paredX
            );
    }

    // Registrar colision vertical
    if (!paredY.empty())
    {
        eventosColisiones.push_back(
            std::to_string(tiempoActual + dt) + ",Pared,"
            + std::to_string(p.getId()) + "," + paredY
            );
    }

}



bool Simulacion::hayColisionObstaculo(
    const Particula& p, const Obstaculo& o) const
{
    double cercanoX = std::max(o.getX(),
                               std::min(p.getX(), o.getX() + o.getLado()));

    double cercanoY = std::max(o.getY(),
                               std::min(p.getY(), o.getY() + o.getLado()));

    double dx = p.getX() - cercanoX;
    double dy = p.getY() - cercanoY;

    return dx * dx + dy * dy <=
           p.getRadio() * p.getRadio();
}


void Simulacion::resolverColisionObstaculo(
    Particula& p, const Obstaculo& o)
{
    double e = 0.8;

    // Punto mas cercano del obstaculo
    double cercanoX = std::max(o.getX(),
                               std::min(p.getX(), o.getX() + o.getLado()));

    double cercanoY = std::max(o.getY(),
                               std::min(p.getY(), o.getY() + o.getLado()));

    // Distancia en cada eje
    double dx = p.getX() - cercanoX;
    double dy = p.getY() - cercanoY;

    double distancia = std::sqrt(dx * dx + dy * dy);


    double nx = 0.0;
    double ny = 0.0;

    if (distancia > 0.0)
    {
        nx = dx / distancia;
        ny = dy / distancia;
    }
    else
    {
        // Distancia del centro a cada lado
        double izquierda = p.getX() - o.getX();
        double derecha = o.getX() + o.getLado() - p.getX();
        double superior = p.getY() - o.getY();
        double inferior = o.getY() + o.getLado() - p.getY();

        // Inicialmente suponemos que el lado izquierdo es el mas cercano
        double menor = izquierda;
        nx = -1.0;
        ny = 0.0;
        cercanoX = o.getX();
        cercanoY = p.getY();

        if (derecha < menor)
        {
            menor = derecha;
            nx = 1.0;
            ny = 0.0;
            cercanoX = o.getX() + o.getLado();
            cercanoY = p.getY();
        }

        if (superior < menor)
        {
            menor = superior;
            nx = 0.0;
            ny = -1.0;
            cercanoX = p.getX();
            cercanoY = o.getY();
        }

        if (inferior < menor)
        {
            nx = 0.0;
            ny = 1.0;
            cercanoX = p.getX();
            cercanoY = o.getY() + o.getLado();
        }
    }


    // Componente perpendicular de la velocidad
    double vn = p.getVx() * nx + p.getVy() * ny;

    // Corregir la posicion
    p.setPosicion(cercanoX + nx * p.getRadio(),
                  cercanoY + ny * p.getRadio());

    // Rebotar solo si se mueve hacia el obstaculo
    if (vn < 0)
    {
        double nuevaVx = p.getVx() - (1 + e) * vn * nx;
        double nuevaVy = p.getVy() - (1 + e) * vn * ny;

        p.setVelocidad(nuevaVx, nuevaVy);
    }
}


bool Simulacion::hayColisionParticulas(
    const Particula& p1, const Particula& p2) const
{
    double dx = p1.getX() - p2.getX();
    double dy = p1.getY() - p2.getY();

    double sumaRadios = p1.getRadio() + p2.getRadio();

    return dx * dx + dy * dy <= sumaRadios * sumaRadios;
}


Particula Simulacion::fusionarParticulas(
    const Particula& p1, const Particula& p2) const
{
    // Nueva masa
    double masaNueva = p1.getMasa() + p2.getMasa();

    // Nueva velocidad
    double vxNueva = (p1.getMasa() * p1.getVx()
                      + p2.getMasa() * p2.getVx()) / masaNueva;

    double vyNueva = (p1.getMasa() * p1.getVy()
                      + p2.getMasa() * p2.getVy()) / masaNueva;

    // Nuevo centro de masa
    double xNueva = (p1.getMasa() * p1.getX()
                     + p2.getMasa() * p2.getX()) / masaNueva;

    double yNueva = (p1.getMasa() * p1.getY()
                     + p2.getMasa() * p2.getY()) / masaNueva;

    // Nuevo radio
    double radioNuevo = std::sqrt(
        p1.getRadio() * p1.getRadio()
        + p2.getRadio() * p2.getRadio()
        );

    // Crear y devolver la nueva particula
    return Particula(xNueva, yNueva, vxNueva, vyNueva,
                     masaNueva, radioNuevo);
}


void Simulacion::ejecutar(int cantidadPasos)
{
    // Limpiar los eventos de colisiones anteriores
    eventosColisiones.clear();

    // Crear el archivo de posiciones
    std::ofstream archivo("posiciones.csv");

    if (!archivo.is_open())
    {
        std::cout << "Error al abrir el archivo." << std::endl;
        return;
    }

    // Encabezados del archivo de posiciones
    archivo << "Paso,Tiempo,Particula,X,Y" << std::endl;

    // Guardar las posiciones iniciales
    for (const Particula& p : particulas)
    {
        archivo << 0 << ","
                << tiempoActual << ","
                << p.getId() << ","
                << p.getX() << ","
                << p.getY() << std::endl;
    }

    // Ejecutar la simulacion
    for (int paso = 1; paso <= cantidadPasos; paso++)
    {
        std::cout << "\nPaso " << paso << ":" << std::endl;

        avanzarPaso();
        mostrarPosiciones();

        // Guardar las posiciones despues de cada paso
        for (const Particula& p : particulas)
        {
            archivo << paso << ","
                    << tiempoActual << ","
                    << p.getId() << ","
                    << p.getX() << ","
                    << p.getY() << std::endl;
        }
    }

    archivo.close();

    // Crear el archivo de colisiones
    std::ofstream archivoColisiones("colisiones.csv");

    if (!archivoColisiones.is_open())
    {
        std::cout << "Error al crear colisiones.csv" << std::endl;
        return;
    }

    // Encabezados del archivo de colisiones
    archivoColisiones << "Tiempo,Tipo,Particula,Detalle,NuevaParticula"
                      << std::endl;

    // Guardar todos los eventos de colision
    for (const std::string& evento : eventosColisiones)
    {
        archivoColisiones << evento << std::endl;
    }

    archivoColisiones.close();

    std::cout << "\nArchivos guardados correctamente."
              << std::endl;
}