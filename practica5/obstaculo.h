#ifndef OBSTACULO_H
#define OBSTACULO_H

class Obstaculo
{
private:
    double x;
    double y;
    double lado;

public:
    Obstaculo(double x, double y, double lado);

    double getX() const;
    double getY() const;
    double getLado() const;
};

#endif // OBSTACULO_H
