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
    std::function<void()> callbackForTouchingEnemy;
    std::function<void(sf::Vector2i)> callbackToGiveRing;
    std::function<void()> callbackToCompleteLevel;
    std::function<void()> callbackForTouchingToLowerItem;
    std::function<void()> callbackForTouchingToUpperItem;

    bool checkRingContact(b2Contact* contact);

public :
    ActorListener(std::function<void()> callbackForTouchingEnemy,
                  std::function<void()> callbackForTouchingToLowerItem,
		          std::function<void()> callbackForTouchingToUpperItem,
                  std::function<void(sf::Vector2i)> callbackToGiveBonus,
                  std::function<void()> callbackToCompleteLevel);

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

};


#endif //BOUNCE_ACTORLISTENER_H
