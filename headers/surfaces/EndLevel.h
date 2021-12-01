//
// Created by oop on 27.11.2021.
//

#ifndef BOUNCE_ENDLEVEL_H
#define BOUNCE_ENDLEVEL_H


#include "Surface.h"

class EndLevel : public Surface{

public:

    EndLevel(const std::string &path, float size);

    b2Fixture* buildOnEngineWithoutTop(b2World& world, float x, float y) override;
    std::pair<b2Fixture*, b2Fixture*> buildOnEngine(b2World& world, float x, float y) override;

};


#endif //BOUNCE_ENDLEVEL_H
