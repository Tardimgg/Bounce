//
// Created by oop on 26.11.2021.
//

#ifndef BOUNCE_ROTATEDRING_H
#define BOUNCE_ROTATEDRING_H


#include "RotatedRingType.h"
#include "../../../headers/Level.h"


class RotatedRing : public RotatedRingType{

private:

    std::vector<b2Vec2> leftRing;
    std::vector<b2Vec2> rightRing;

public:

    RotatedRing(const std::string &path, float size);

    b2Fixture* buildOnEngineWithoutTop(b2World& world, float x, float y) override;
    std::pair<b2Fixture*, b2Fixture*> buildOnEngine(b2World& world, float x, float y) override;

};


#endif //BOUNCE_ROTATEDRING_H
