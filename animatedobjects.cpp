#include "animatedobjects.h"
#include "cannon.h"
#include "scope.h"
#include "menu.h"
#include "sdlmixer.h"
#include "window.h"
#include "gameobjects.h"
#include "glwidget.h"

namespace AnimatedObjects
{
    Cannon *_cannon;
    Scope *_scope;

    double _shootAnimationTime;
    bool shootAnimation;

    Mesh *base;

    GLWidget *_widget;
}

void AnimatedObjects::init(GLWidget *widget)
{
    _cannon = new Cannon();
    _scope = new Scope();

    _shootAnimationTime = 0;
    shootAnimation = false;

    base = new Mesh("base", 0, -Window::height() / 2 + 51 / 2 + 20);

    _widget = widget;
}

void AnimatedObjects::update(double dt)
{
    if(shootAnimation && _shootAnimationTime >= 0.6) shootAnimation = false;
    const QPoint &mousePos = _widget->mousePos();

    if (!Menu::menu()) {
        const double x = mousePos.x();
        const double y = mousePos.y() + Window::height() / 2 - 60;
        _cannon->setRotation(atan(y / x) * 180 / M_PI);
        if (x < 0) _cannon->addToRot(180);
    }
    if(shootAnimation) _shootAnimationTime += dt;
}

void AnimatedObjects::mousePressEvent()
{
    //can't  shoot too fast, need to wait until animation is finnished
    if (shootAnimation) return;
    //can't shoot if cannon is directed to ground
    if (_cannon->rotation() > 176 || _cannon->rotation() < 4) return;

    SdlMixer::shoot().play();
    GameObjects::addCannonBall(_cannon->rotation());
    shootAnimation = true;
    _shootAnimationTime = 0;
}

double AnimatedObjects::animate(double min, double max)
{
    if (shootAnimation) {
        if (_shootAnimationTime < 0.1) return min + (max - min) * 10 * _shootAnimationTime;
        if (_shootAnimationTime >= 0.1 && _shootAnimationTime < 0.6) return max - (max - min) * 2 * (_shootAnimationTime - 0.1);
        if (_shootAnimationTime >= 0.6) return min;
    }
    else return min;
}

void AnimatedObjects::drawCannon()
{
    _cannon->draw();
    base->draw();
}

Mesh &AnimatedObjects::scope()
{
    return *_scope;
}

double AnimatedObjects::shootAnimationTime()
{
    return _shootAnimationTime;
}
