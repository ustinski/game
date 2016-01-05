#ifndef ANIMATEDOBJECTS_H
#define ANIMATEDOBJECTS_H

class GLWidget;
class Mesh;

namespace AnimatedObjects
{
    void init(GLWidget *widget);
    void drawCannon();
    Mesh &scope();
    double shootAnimationTime();

    void update(double dt);
    void mousePressEvent();

    double animate(double min, double max);
};

#endif // ANIMATEDOBJECTS_H
