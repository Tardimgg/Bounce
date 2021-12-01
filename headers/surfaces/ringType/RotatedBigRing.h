//
// Created by oop on 30.11.2021.
//

#ifndef BOUNCE_ROTATEDBIGRING_H
#define BOUNCE_ROTATEDBIGRING_H

#include "RotatedRingType.h"

class RotatedBigRing : public RotatedRingType{

private:

    std::vector<b2Vec2> leftRing;
    std::vector<b2Vec2> rightRing;

public:

    RotatedBigRing(const std::string &path, float size);

    b2Fixture* buildOnEngineWithoutTop(b2World& world, float x, float y) override;
    std::pair<b2Fixture*, b2Fixture*> buildOnEngine(b2World& world, float x, float y) override;

};


#endif //BOUNCE_ROTATEDBIGRING_H