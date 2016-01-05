#include "listener.h"
#include "bubble.h"

void Listener::BeginContact(b2Contact* contact) {
    void *dataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void *dataB = contact->GetFixtureB()->GetBody()->GetUserData();

    //if ball colides with wall
    if(!dataA || !dataB) {
        void *data = dataA ? dataA : dataB;
        Circle *circle = static_cast<Circle*>(data);
        if(circle->type() == Circle::CANNONBALL) circle->beginContact();
    }

    //cannonball and bubble
    if(dataA && dataB) {
        Circle *circleA = static_cast<Circle*>(dataA);
        Circle *circleB = static_cast<Circle*>(dataB);

        if(circleA->type() != circleB->type()) {
            Circle *bubble = circleA->type() == Circle::BUBBLE ? circleA : circleB;
            Circle *ball = circleA->type() == Circle::CANNONBALL ? circleA : circleB;

            bubble->beginContact();
            static_cast<Bubble*>(bubble)->setBall(ball);
        }
    }
}

