//
// Created by oop on 03.11.2021.
//

#ifndef BOUNCE_SPIKE_H
#define BOUNCE_SPIKE_H


#include "Surface.h"

class Spike : public Surface {

public:

    Spike(const std::string &path, float size);

    b2Fixture* buildOnEngineWithoutTop(b2World& world, float x, float y) override;
    std::pair<b2Fixture*, b2Fixture*> buildOnEngine(b2World& world, float x, float y) override;



};


#endif //BOUNCE_SPIKE_H
