#include "circle.h"
#include "gameobjects.h"
#include "window.h"

Circle::Circle()
{
    //_effCont = widget->effCont();
    //_effect = 0;
	_exists = true;
	_destroyedTime = 0;

    shadow = 0;
    _contact = false;
}

Circle::~Circle()
{
    delete shadow;
    Physics::world()->DestroyBody(_body);
}

const QVector2D Circle::speed() const
{
    const b2Vec2 &speed = _body->GetLinearVelocity();
    return QVector2D(speed.x, speed.y);
}

void Circle::setPosition(double x, double y)
{
    Mesh::setPosition(x, y);
    shadow->setPosition(x, -Window::height() / 2 + Window::ground() + 4);
}

/*EffectsContainer *Circle::effCont() const
{
	return _effCont;
}*/

void Circle::stopEffect()
{
//	if (_effect) _effect->Finish();
}

void Circle::draw(Element element)
{
    if (element == SHADOW) shadow->draw();
    if (element == BODY) Mesh::draw();
}

void Circle::update()
{
    /*if (!_effect) return;
	_effect->posX = _position.x();
    _effect->posY = _position.y();*/

    b2Vec2 position = Physics::scale() * _body->GetPosition();
    setPosition(position.x, position.y);
}

void Circle::initVertices()
{
    int width = radius() * 2;
    Mesh::initVertices(width, width);
}

void Circle::createShadow(int size)
{
    int width = size == 0 ? 15 : size * 50;
    shadow = new Mesh(GameObjects::shadow(size), _position.x(), -Window::height() / 2 + Window::ground(), width, width / 5);
}

void Circle::createBody()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    _body = Physics::world()->CreateBody(&bodyDef);
    _body->SetUserData(this);
}

void Circle::createFixture(int radius, int density, int restitution)
{
    b2FixtureDef fixtureDef;
    {
        b2CircleShape *circleShape = new b2CircleShape;
        circleShape->m_p.Set(0, 0);
        circleShape->m_radius = radius / Physics::scale();
        fixtureDef.shape = circleShape;
    }

    fixtureDef.density = density;
    fixtureDef.friction = 0;
    fixtureDef.restitution = restitution;

    _body->CreateFixture(&fixtureDef);
}
