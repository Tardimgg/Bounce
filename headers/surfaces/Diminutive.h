//
// Created by oop on 30.11.2021.
//

#ifndef BOUNCE_DIMINUTIVE_H
#define BOUNCE_DIMINUTIVE_H

#include "Surface.h"
#include "../../headers/Level.h"


class Diminutive : public Surface{

public:

    Diminutive(const std::string &path, float size);

    b2Fixture* buildOnEngineWithoutTop(b2World& world, float x, float y) override;
    std::pair<b2Fixture*, b2Fixture*> buildOnEngine(b2World& world, float x, float y) override;

};


#endif //BOUNCE_DIMINUTIVE_H
