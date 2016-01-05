#ifndef REFRACTION_H
#define REFRACTION_H

#include "mesh.h"

class GLWidget;

class Refraction : public Mesh
{
public:
    Refraction(int radius, QOpenGLTexture *texture, double x, double y, int width, int height);

    void draw();

private:
    int _radius;
};

#endif // REFRACTION_H
