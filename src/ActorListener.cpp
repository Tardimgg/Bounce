//
// Created by oop on 22.11.2021.
//

#include "../headers/ActorListener.h"
#include <iostream>
#include <utility>


ActorListener::ActorListener(std::function<void()> callbackForTouchingEnemy,
			     std::function<void()> callbackForTouchingToLowerItem,
			     std::function<void()> callbackForTouchingToUpperItem,
			     std::function<void(sf::Vector2i)> callbackToGiveRing,
                             std::function<void()> callbackToCompleteLevel) : b2ContactListener(),
                                                                              callbackForTouchingEnemy(std::move(callbackForTouchingEnemy)),
                                                                              callbackForTouchingToLowerItem(std::move(callbackForTouchingToLowerItem)),
                                                                              callbackForTouchingToUpperItem(std::move(callbackForTouchingToUpperItem)),
                                                                              callbackToGiveRing(std::move(callbackToGiveRing)),
                                                                              callbackToCompleteLevel(std::move(callbackToCompleteLevel)){

}

void ActorListener::EndContact(b2Contact *contact) {
    b2ContactListener::EndContact(contact);
}

void ActorListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
    b2ContactListener::PreSolve(contact, oldManifold);

    if (contact->GetFixtureA()->GetUserData().pointer & ENEMY && contact->GetFixtureB()->GetUserData().pointer & BALL_TYPE ||
        contact->GetFixtureB()->GetUserData().pointer & ENEMY && contact->GetFixtureA()->GetUserData().pointer & BALL_TYPE) {
        this->callbackForTouchingEnemy();
        return;
    }

    if (contact->GetFixtureA()->GetUserData().pointer & END_LEVEL_TYPE ||
        contact->GetFixtureB()->GetUserData().pointer & END_LEVEL_TYPE) {
        this->callbackToCompleteLevel();
        return;
    }

    if (contact->GetFixtureA()->GetUserData().pointer & TO_LOWER_ITEM_TYPE ||
        contact->GetFixtureB()->GetUserData().pointer & TO_LOWER_ITEM_TYPE) {
        this->callbackForTouchingToLowerItem();
        return;
    }
    if (contact->GetFixtureA()->GetUserData().pointer & TO_UPPER_ITEM_TYPE ||
        contact->GetFixtureB()->GetUserData().pointer & TO_UPPER_ITEM_TYPE) {
        this->callbackForTouchingToUpperItem();
        return;
    }

    if (checkRingContact(contact)) {
        if ((sf::Vector2i*)(contact->GetFixtureA()->GetBody()->GetUserData().pointer) != nullptr) {
            this->callbackToGiveRing(*(sf::Vector2i*)(contact->GetFixtureA()->GetBody()->GetUserData().pointer));
        } else if ((sf::Vector2i*)(contact->GetFixtureB()->GetBody()->GetUserData().pointer) != nullptr) {
            this->callbackToGiveRing(*(sf::Vector2i*)(contact->GetFixtureB()->GetBody()->GetUserData().pointer));
        }
    }
}

void ActorListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
    b2ContactListener::PostSolve(contact, impulse);
}

void ActorListener::BeginContact(b2Contact *contact) {
    b2ContactListener::BeginContact(contact);

}

bool ActorListener::checkRingContact(b2Contact* contact) {
    if (contact->GetFixtureA()->GetUserData().pointer & ORDINARY_RING_TYPE ||
        contact->GetFixtureB()->GetUserData().pointer & ORDINARY_RING_TYPE) {
        if (std::abs(contact->GetManifold()->localNormal.y) >= 0.79) {
            return true;
        }
    }

    if (contact->GetFixtureA()->GetUserData().pointer & ROTATED_RING_TYPE ||
        contact->GetFixtureB()->GetUserData().pointer & ROTATED_RING_TYPE) {
        if (std::abs(contact->GetManifold()->localNormal.x) >= 0.79) {
            return true;
        }
    }

    if (contact->GetFixtureA()->GetUserData().pointer & ORDINARY_BIG_RING_TYPE ||
        contact->GetFixtureB()->GetUserData().pointer & ORDINARY_BIG_RING_TYPE) {
        if (std::abs(contact->GetManifold()->localNormal.y) >= 0.1) {
            return true;
        }
    }

    if (contact->GetFixtureA()->GetUserData().pointer & ROTATED_BIG_RING_TYPE ||
        contact->GetFixtureB()->GetUserData().pointer & ROTATED_BIG_RING_TYPE) {
        if (std::abs(contact->GetManifold()->localNormal.x) >= 0.1) {
            return true;
        }
    }

    //if (contact->GetFixtureA()->GetUserData().pointer & BONUS || contact->GetFixtureB()->GetUserData().pointer & BONUS) {
    //    return true;
    //}
    return false;
}



