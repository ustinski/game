#ifndef LISTENER_H
#define LISTENER_H

#include "physics.h"

class Listener : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact);
};

#endif // LISTENER_H
