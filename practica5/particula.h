#ifndef PARTICULA_H
#define PARTICULA_H

class Particula
{
private:
    double x;
    double y;
    double vx;
    double vy;
    double masa;
    double radio;

public:
    Particula();

    Particula(double x, double y, double vx, double vy, double masa, double radio);

    double getX() const;
    double getY() const;
    double getVx() const;
    double getVy() const;
    double getMasa() const;
    double getRadio() const;

    void mover(double dt);

    void setVelocidad(double nuevaVx, double nuevaVy);


};

#endif // PARTICULA_H
