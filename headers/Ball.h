//
// Created by oop on 03.11.2021.
//

#ifndef BOUNCE_BALL_H
#define BOUNCE_BALL_H


#include "FlyingView.h"
#include "../include/box2d/b2_fixture.h"
#include "../include/box2d/box2d.h"


class Ball : public FlyingView {

public:

    explicit Ball(const std::string& path);

    std::pair<b2Body*, b2Fixture*> buildOnEngine(b2World& world, float radius, float x, float y);


};


#endif //BOUNCE_BALL_H
