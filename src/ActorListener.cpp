//
// Created by oop on 22.11.2021.
//

#include "../headers/ActorListener.h"
#include <iostream>
#include <utility>


ActorListener::ActorListener(TypeFigure valueForCallback, std::function<void()> callback) : b2ContactListener(),
                                                                                      valueForCallback(valueForCallback),
                                                                                      callback(std::move(callback)){

}

void ActorListener::EndContact(b2Contact *contact) {
    b2ContactListener::EndContact(contact);
}

void ActorListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
    b2ContactListener::PreSolve(contact, oldManifold);
}

void ActorListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
    b2ContactListener::PostSolve(contact, impulse);
}

void ActorListener::BeginContact(b2Contact *contact) {
    b2ContactListener::BeginContact(contact);
    if (contact->GetFixtureA()->GetUserData().pointer & this->valueForCallback ||
        contact->GetFixtureB()->GetUserData().pointer & this->valueForCallback) {

        this->callback();
    }
}


