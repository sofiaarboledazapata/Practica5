#include "caja.h"

Caja::Caja(double ancho, double alto)
    : ancho(ancho), alto(alto)
{
}

double Caja::getAncho() const
{
    return ancho;
}

double Caja::getAlto() const
{
    return alto;
}
