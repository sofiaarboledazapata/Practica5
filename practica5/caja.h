#ifndef CAJA_H
#define CAJA_H

class Caja
{
private:
    double ancho;
    double alto;

public:
    Caja(double ancho, double alto);

    double getAncho() const;
    double getAlto() const;
};

#endif // CAJA_H

