#include "bubble.h"
#include "window.h"
#include "gameobjects.h"
#include "refraction.h"

//random
float ran(int min, int max, bool isSigned = false);

Bubble::Bubble()
{
    refraction = 0;
    createBody();
    first = true;
    _type = BUBBLE;
}

void Bubble::destroy()
{
    //ParticleEffectPtr eff = _effCont->AddEffect("bubble" + lexical_cast(2 * _radius));
    //eff->posX = _position.x();
    //eff->posY = _position.y();
    //eff->Reset();
	_exists = false;
    _body->SetActive(false);
}

void Bubble::draw(Element element)
{
	//bubble is drawn only if it exists, cannonball is draws even if it does not exists (lies on ground)
    if(!_exists) return;
    if(element == BODY) refraction->draw();
    Circle::draw(element);
}

//void Bubble::update()
//{ line->setAngle(_body->GetAngle()); }

void Bubble::resetParams()
{
    using namespace Window;
    _position = {ran(-width() / 2 + 75, width() / 2 - 75), ran(-height() / 2 + ground() + 75, height() / 2 - 75)};
    int size = 1 + rand() % 3;
    _radius = size * 25;
}

void Bubble::resetAll()
{
    resetPhysics();
    resetGraphics();
    _exists = true;
    _destroyedTime = 0;
}

void Bubble::resetPhysics()
{
    _body->SetTransform(1 / Physics::scale() * b2Vec2(_position.x(), _position.y()), 0);
    _body->SetLinearVelocity(b2Vec2(ran(10, 25,  true), ran(10, 25, true)));
    if(first) first = false;
    else _body->DestroyFixture(_body->GetFixtureList());
    createFixture(_radius, 1, 1);
    _body->SetActive(true);
    _contact = false;
}

void Bubble::resetGraphics()
{
    //const b2Vec2 &pos = _body->GetPosition();
    //_position = {pos.x, pos.y};
    //_position *= Physics::scale();
    int size = _radius / 25;
    _texture = GameObjects::circle(size);
    Circle::initVertices();
    delete shadow;
    createShadow(size);
    delete refraction;
    refraction = new Refraction(_radius, GameObjects::refraction(size - 1), _position.x(), _position.y(), 2 * _radius, 2 * _radius);
}

void Bubble::move(const QVector2D &dr)
{
    Circle::move(dr);
    refraction->move(dr);
}

void Bubble::setPosition(double x, double y)
{
    Circle::setPosition(x, y);
    refraction->setPosition(x, y);
}

float ran(int min, int max, bool isSigned)
{
    int ans = (min + rand() % (max - min));
    if(isSigned) ans *= ((rand() % 2) * 2 - 1);
    return ans;
}
