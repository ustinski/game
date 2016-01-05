#include "physics.h"
#include "window.h"
#include "listener.h"

namespace Physics
{
    b2World *_world;
    Listener _listener;
    const double sc = 10;


    void createBox(int x, int y, int hWidth, int hHeight);
}

void Physics::init()
{
    _world = new b2World(b2Vec2(0, 0));
    _world->SetContactListener(&_listener);


    using namespace Window;
    const int hw = 10;
    createBox(0, height() / 2 / sc + hw, width() / 2 / sc, hw);
    createBox(0, -height() / 2 / sc + ground() / sc - hw, width() / 2 / sc, hw);
    createBox(-width() / 2 / sc - hw, 0, hw, height() / 2 / sc);
    createBox(width() / 2 / sc + hw, 0, hw, height() / 2 / sc);
}

void Physics::createBox(int x, int y, int hWidth, int hHeight)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(x, y);

    b2PolygonShape box;
    box.SetAsBox(hWidth, hHeight);

    b2Body *body = _world->CreateBody(&bodyDef);
    body->CreateFixture(&box, 0);
}

void Physics::update(double dt)
{
    _world->Step(dt, 6, 2);
    //for (int i = 0; i < objectList.size(); i++) objectList[i]->update();
}

b2World *Physics::world() { return _world; }
double Physics::scale() { return sc; }
