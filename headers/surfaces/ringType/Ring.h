//
// Created by oop on 25.11.2021.
//

#ifndef BOUNCE_RING_H
#define BOUNCE_RING_H


#include "../../Level.h"
#include "RingType.h"


class Ring : public RingType{

private:

    std::vector<b2Vec2> upperRing;
    std::vector<b2Vec2> lowerRing;

public:

    Ring(const std::string &path, float size);

    b2Fixture* buildOnEngineWithoutTop(b2World& world, float x, float y) override;
    std::pair<b2Fixture*, b2Fixture*> buildOnEngine(b2World& world, float x, float y) override;


};


#endif //BOUNCE_RING_H
