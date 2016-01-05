#ifndef CANNON_H
#define CANNON_H

#include "mesh.h"

class Cannon : public Mesh
{
public:
    Cannon();

    void prepareMatrix();

    double rotation()
    { return _rotation; }

    void addToRot(double value)
    { _rotation += value; }

    void setRotation(double value)
    { _rotation = value; }

private:
    double _rotation;
};

#endif // CANNON_H
