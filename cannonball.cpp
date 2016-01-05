#include "cannonball.h"
#include "gameobjects.h"
#include "window.h"
#include "physics.h"

CannonBall::CannonBall(double cannonRotation)
{
    initPhysics(cannonRotation);
    initGraphics();
    _type = CANNONBALL;
    GameObjects::decreaseScore();
}

void CannonBall::initPhysics(double cannonRotation)
{
    createBody();
    cannonRotation *= M_PI / double(180);
    QVector2D direction(cos(cannonRotation), sin(cannonRotation));
    QVector2D position = QVector2D(0, -Window::height() / 2 + Window::ground() + 20) + direction * 90;
    _body->SetTransform(1 / Physics::scale() * b2Vec2(position.x(), position.y()), 0);
    _body->SetLinearVelocity(GameObjects::speed() / Physics::scale() * b2Vec2(direction.x(), direction.y()));
    createFixture(8, 35, 0);
}

void CannonBall::initGraphics()
{
    const b2Vec2 &pos = _body->GetPosition();
    _position = {pos.x, pos.y};
    _position *= Physics::scale();
    //_speed = direction * GameObjects::speed();
    Circle::initVertices();
    _texture = GameObjects::circle(0);
    createShadow(0);

    /*_effect = _effCont->AddEffect("flame");
    _effect->posX = _position.x();
    _effect->posY = _position.y();
    _effect->Reset();*/
}

void CannonBall::destroy()
{
	//after stopEffect() ball lies on ground without flames
    //stopEffect();
    //_effect = 0;
	_exists = false;
}

void CannonBall::update()
{
    Circle::update();
    double radScaled = radius() / Physics::scale();
    _body->ApplyForceToCenter(b2Vec2(0, -35 * 150 / Physics::scale() * M_PI * radScaled * radScaled), true);

}
