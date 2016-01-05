#ifndef CANNONBALL_H
#define CANNONBALL_H

#include "circle.h"

class CannonBall : public Circle
{
public:
    CannonBall(double cannonRotation);
    void initPhysics(double cannonRotation);
    void initGraphics();

    void destroy();
    void update();
};

#endif // CANNONBALL_H
