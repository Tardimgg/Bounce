//
// Created by oop on 22.11.2021.
//

#ifndef BOUNCE_ACTORLISTENER_H
#define BOUNCE_ACTORLISTENER_H


#include "../include/box2d/b2_world_callbacks.h"
#include "../include/box2d/box2d.h"
#include "../headers/Level.h"
#include <functional>

class ActorListener : public b2ContactListener {

private:
    TypeFigure valueForCallback;
    std::function<void()> callback;

public :
    ActorListener(TypeFigure valueForCallback, std::function<void()> callback);

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

};


#endif //BOUNCE_ACTORLISTENER_H
