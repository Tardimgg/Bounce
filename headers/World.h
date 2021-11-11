//
// Created by oop on 03.11.2021.
//

#ifndef BOUNCE_WORLD_H
#define BOUNCE_WORLD_H


#include <SFML/Graphics/Sprite.hpp>
#include "Environment.h"
#include "Ball.h"

class World {

private:
    sf::Sprite worldSprite;
    sf::Sprite ballSprite;
    Environment block = Environment("../data/cellNew.png");
    Ball ball = Ball("../data/ball.png");
    sf::Vector2f powerVectorOnBall = sf::Vector2f(0, 0);

public:
    World();

    sf::Vector2f update(int elapsed);

    void input(sf::Keyboard::Key addPowerVector);

    void drawTexture(sf::RenderWindow& worldWindows, unsigned int width, unsigned int height);
};


#endif //BOUNCE_WORLD_H
