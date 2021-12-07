//
// Created by oop on 30.11.2021.
//

#ifndef BOUNCE_BIGRING_H
#define BOUNCE_BIGRING_H

#include "RingType.h"
#include "../../../headers/Level.h"

class BigRing : public RingType{

public:

    BigRing(const std::string &path, float size);

    b2Fixture* buildOnEngineWithoutTop(b2World& world, float x, float y) override;
    std::pair<b2Fixture*, b2Fixture*> buildOnEngine(b2World& world, float x, float y) override;

};




#endif //BOUNCE_BIGRING_H
