#include "particula.h"

Particula::Particula()
    : x(0.0), y(0.0),
    vx(0.0), vy(0.0),
    masa(1.0), radio(1.0), id(0)
{
}

Particula::Particula(double x, double y, double vx, double vy,
                     double masa, double radio)
    : x(x), y(y),
    vx(vx), vy(vy),
    masa(masa), radio(radio), id(0)
{
}



double Particula::getX() const
{
    return x;
}

double Particula::getY() const
{
    return y;
}

double Particula::getVx() const
{
    return vx;
}

double Particula::getVy() const
{
    return vy;
}

double Particula::getMasa() const
{
    return masa;
}

double Particula::getRadio() const
{
    return radio;
}

void Particula::mover(double dt)
{
    x = x + vx * dt;
    y = y + vy * dt;
}


void Particula::setVelocidad(double nuevaVx, double nuevaVy)
{
    vx = nuevaVx;
    vy = nuevaVy;
}

void Particula::setPosicion(double nuevaX, double nuevaY)
{
    x = nuevaX;
    y = nuevaY;
}


int Particula::getId() const
{
    return id;
}

void Particula::setId(int nuevoId)
{
    id = nuevoId;
}

