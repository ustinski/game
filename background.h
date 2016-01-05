#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "mesh.h"

class Background : public Mesh
{
public:
    Background() : Mesh("background", 0, 0) {}
    void draw();

    QOpenGLTexture *texture() { return _texture; }
};

#endif // BACKGROUND_H
