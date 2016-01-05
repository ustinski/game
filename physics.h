#ifndef PHYSICS_H
#define PHYSICS_H

#include <Box2D/Box2D.h>

namespace Physics
{
    void init();
    void update(double dt);

    b2World *world();
    double scale();
};

#endif // PHYSICS_H
