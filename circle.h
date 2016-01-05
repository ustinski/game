#ifndef CIRCLE_H
#define CIRCLE_H

#include "mesh.h"
#include "physics.h"

class Circle : public Mesh
{
public:
    ~Circle();
    const QVector2D &position() const { return _position; }
    const QVector2D speed() const;
    int radius() const
    { return _body->GetFixtureList()->GetShape()->m_radius * Physics::scale(); }
    //EffectsContainer *effCont() const;
    virtual void setPosition(double x, double y);

    bool exists() const { return _exists; }
	void stopEffect();
    void addDestroyedTime(double dt) { _destroyedTime += dt; }
    double destroyedTime() const { return _destroyedTime; }

	enum Element { SHADOW, BODY };
    void draw(Element element);
    void update();

    void beginContact() { _contact = true; }
    bool contact() { return _contact; }
    enum Type {BUBBLE, CANNONBALL};
    Type type() { return _type; }
	
protected:
    Circle();

    //ParticleEffectPtr _effect;
    //EffectsContainer *_effCont;

	bool _exists;
    double _destroyedTime;

    Mesh *shadow;

    b2Body *_body;
    bool _contact;
    Type _type;

    void initVertices();
    void createShadow(int size);
    void createBody();
    void createFixture(int radius, int density, int restitution);
};

#endif // CIRCLE_H
