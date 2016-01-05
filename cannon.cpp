#include "cannon.h"
#include "animatedobjects.h"
#include "window.h"

Cannon::Cannon() : Mesh("cannon", 0, -Window::height() / 2 + 139 / 2 + 30)
{
    _rotation = 80;
}

void Cannon::prepareMatrix()
{
    //additional transformation after translation (rotation)
    Mesh::prepareMatrix();
    double offset = AnimatedObjects::animate(40, 30);
    model.translate(0, -40, 0);
    model.rotate(_rotation - 90, 0, 0, 1);
    model.translate(0, offset, 0);
}
