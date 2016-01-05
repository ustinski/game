#include "scope.h"
#include "animatedobjects.h"

void Scope::prepareMatrix()
{
    Mesh::prepareMatrix();
    double scale = AnimatedObjects::animate(0.5, 1);
    model.rotate(AnimatedObjects::shootAnimationTime() * 150, 0, 0, 1);
    model.scale(scale, scale, 1);
}
