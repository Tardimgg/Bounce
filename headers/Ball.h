//
// Created by oop on 03.11.2021.
//

#ifndef BOUNCE_BALL_H
#define BOUNCE_BALL_H


#include "View.h"

class Ball : public View {

private:

    sf::Vector2f speedVector;

public:

    explicit Ball(const std::string& path);

    sf::Vector2f getSpeedVector();
    void setSpeedVector(sf::Vector2f newSpeedVector);
    void setSpeedVector(float x, float y);


};


#endif //BOUNCE_BALL_H
