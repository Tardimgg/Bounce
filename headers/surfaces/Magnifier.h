//
// Created by oop on 30.11.2021.
//

#ifndef BOUNCE_MAGNIFIER_H
#define BOUNCE_MAGNIFIER_H

#include "Surface.h"
#include "../../headers/Level.h"

class Magnifier : public Surface{

public:

    Magnifier(const std::string &path, float size);

    b2Fixture* buildOnEngineWithoutTop(b2World& world, float x, float y) override;
    std::pair<b2Fixture*, b2Fixture*> buildOnEngine(b2World& world, float x, float y) override;

};



#endif //BOUNCE_MAGNIFIER_H
