#ifndef BUBBLE_H
#define BUBBLE_H

#include "circle.h"

class Refraction;

class Bubble : public Circle
{
public:
    Bubble();
	void destroy();
	void draw(Element element);
    void resetParams();
    void resetAll();


    void move(const QVector2D &dr);
    void setPosition(double x, double y);
    void setBall(Circle *ball) { _ball = ball; }
    const Circle &ball() { return *_ball; }
    int radius() { return _radius; }

private:
    Refraction *refraction;

    int _radius;

    bool first;
    Circle *_ball;

    void resetPhysics();
    void resetGraphics();
};

#endif // BUBBLE_H
