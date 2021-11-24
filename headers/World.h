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
#include "surfaces/Surface.h"
#include "../headers/ActorListener.h"
#include <iostream>

#define sizeOfBlockInMeters 1.25f
#define visibleHeightByBlock 10
#define addedEdges 6
#define OXDamping 0.99f
#define gravityOnY 25.0f
#define jumpSizeByBlock 4.5f
#define maxSpeedOX 10

class World {

private:

    std::unordered_map<LevelItem, Surface*> mapItems;

    int numberLives;

    Ball ball;
    Level level;
    bool flagBallForDelete = false;

    unsigned int widthWindow;
    unsigned int heightWindow;

    float coefForDisplay;

    b2ContactListener* contactListener;

    b2World physicalWorld = b2World(b2Vec2(0.0f, gravityOnY));
    //b2World physicalWorld = b2World(b2Vec2(0.0f, 0));
    b2Body* ballBody;

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
