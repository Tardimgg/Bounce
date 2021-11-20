//
// Created by oop on 03.11.2021.
//

#ifndef BOUNCE_WORLD_H
#define BOUNCE_WORLD_H


#include <SFML/Graphics/Sprite.hpp>
#include "Environment.h"
#include "Ball.h"
#include "Level.h"
#include "../include/box2d/box2d.h"
#include "Surface.h"

class World {

private:
    sf::Sprite worldSprite;
    sf::Sprite ballSprite;

    std::unordered_map<LevelItem, Surface> mapItems;

    Ball ball;
    Level level;

    unsigned int widthWindow;
    unsigned int heightWindow;

    const unsigned int visibleHeightByBlock = 10;
    const int addedEdges = 6;
    const float sizeOfBlockInMeters = 1.25;

    float coef;
    const float gravityOnY = 150.8f;
    const float jumpSizeByBlock = 4.5f;



    b2World physicalWorld = b2World(b2Vec2(0.0f, this->gravityOnY));
    //b2World physicalWorld = b2World(b2Vec2(0.0f, 0));
    b2Body* ballBody;
    b2CircleShape dynamicBallShape;

    void createSurface();

public:
    World(Level level, unsigned int width, unsigned int height);

    sf::Vector2f getMainObjectPosition();

    sf::Vector2f update(long long elapsedTime);

    void input(sf::Keyboard::Key addPowerVector);

    void drawTexture(sf::RenderWindow& worldWindows);


};


#endif //BOUNCE_WORLD_H
