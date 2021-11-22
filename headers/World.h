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
#include "../headers/ActorListener.h"
#include <iostream>



class World {

private:
    sf::Sprite ballSprite;

    std::unordered_map<LevelItem, sf::Sprite> mapSprites;
    std::unordered_map<LevelItem, Surface> mapItems;

    int numberLives;

    Ball ball;
    Level level;
    bool flagBallForDelete = false;

    unsigned int widthWindow;
    unsigned int heightWindow;

    const unsigned int visibleHeightByBlock = 10;
    const int addedEdges = 6;
    const float sizeOfBlockInMeters = 1.25;

    float coefForDisplay;
    float OXDamping = 0.99f;
    const float gravityOnY = 25.0f;
    const float jumpSizeByBlock = 4.5f;
    const float maxSpeedOX = 10;

    b2ContactListener* contactListener;

    b2World physicalWorld = b2World(b2Vec2(0.0f, this->gravityOnY));
    //b2World physicalWorld = b2World(b2Vec2(0.0f, 0));
    b2Body* ballBody;
    b2CircleShape dynamicBallShape;

    void createSurfaces();
    void createSprites();
    void touchingEnemy();
    void createBall();

public:
    World(Level level, unsigned int width, unsigned int height);

    sf::Vector2f getMainObjectPosition();

    sf::Vector2f update(long long elapsedTime);

    void input(sf::Keyboard::Key addPowerVector);

    void drawTexture(sf::RenderWindow& worldWindows);


};


#endif //BOUNCE_WORLD_H
