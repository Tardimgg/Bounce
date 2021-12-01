//
// Created by oop on 03.11.2021.
//

#ifndef BOUNCE_FLYINGVIEW_H
#define BOUNCE_FLYINGVIEW_H


#include "Environment.h"
#include "../include/box2d/b2_fixture.h"
#include "../include/box2d/box2d.h"

class FlyingView : public Environment {

private:
    sf::Vector2f position;

public:

    explicit FlyingView(const std::string &path);

    void setPosition(sf::Vector2f position);

    sf::Vector2f getPosition();

    void setPosition(float width, float height);

    void buildSprite(float scaleCoefOX, float scaleCoefOY) override;

};


#endif //BOUNCE_FLYINGVIEW_H
