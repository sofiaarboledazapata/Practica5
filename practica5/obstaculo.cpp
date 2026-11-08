#include "obstaculo.h"

Obstaculo::Obstaculo(double x, double y, double lado)
    : x(x), y(y), lado(lado)
{
}

double Obstaculo::getX() const
{
    return x;
}

double Obstaculo::getY() const
{
    return y;
}

double Obstaculo::getLado() const
{
    return lado;
}

