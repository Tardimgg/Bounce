//
// Created by oop on 03.11.2021.
//

#ifndef BOUNCE_BALL_H
#define BOUNCE_BALL_H


#include "FlyingView.h"
#include "../headers/Level.h"


class Ball : public FlyingView {

private:
    bool ballIsSmall = true;

public:

    explicit Ball(const std::string& path);

    std::pair<b2Body*, b2Fixture*> buildOnEngine(b2World& world, float radius, float x, float y);

    bool isSmall();
    void setSmallSize(bool smallSize);
    
};


#endif //BOUNCE_BALL_H
