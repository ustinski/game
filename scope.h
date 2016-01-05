#ifndef SCOPE_H
#define SCOPE_H

#include "mesh.h"

class Scope : public Mesh
{
public:
    Scope() : Mesh("scope", 0, 0) {}

    void prepareMatrix();
};

#endif // SCOPE_H
