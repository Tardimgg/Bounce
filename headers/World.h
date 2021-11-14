//
// Created by oop on 03.11.2021.
//

#ifndef BOUNCE_WORLD_H
#define BOUNCE_WORLD_H


#include <SFML/Graphics/Sprite.hpp>
#include "Environment.h"
#include "Ball.h"
#include "Level.h"

class World {

private:
    sf::Sprite worldSprite;
    sf::Sprite ballSprite;
    Environment block = Environment("../data/cell.png");
    Ball ball = Ball("../data/ball.png");
    sf::Vector2f powerVectorOnBall = sf::Vector2f(0, 0);
    Level level;
    unsigned int widthWindow;
    unsigned int heightWindow;

public:
    World(Level level, unsigned int width, unsigned int height);

    sf::Vector2f getMainObjectPosition();

    sf::Vector2f update(long long elapsedTime);

    void input(sf::Keyboard::Key addPowerVector);

    void drawTexture(sf::RenderWindow& worldWindows);


};


#endif //BOUNCE_WORLD_H
