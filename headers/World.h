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
#include "Spider.h"
#include <iostream>

#define sizeOfBlockInMeters 1.25f
#define visibleHeightByBlock 10
#define addedEdges 10
#define OXDamping 0.99f
#define gravityOnY 25.0f
#define jumpSizeByBlock 4.5f
#define maxSpeedOX 9.8f

class World {

private:

    std::unordered_map<LevelItem, Surface*> mapItems;

    std::vector<std::pair<Spider, b2Body*>> spiders;

    int numberLives;
    int numberUnvisitedRings;
    bool finish = false;

    std::vector<std::pair<int, int>> arrangementOfRing;

    Ball ball;
    Level level;
    bool flagBallForDelete = false;
    bool flagBallToLower = false;
    bool flagBallToUpper = false;
    bool ballIsSmall = true;

    unsigned int widthWindow;
    unsigned int heightWindow;

    float coefForDisplay;

    b2ContactListener* contactListener;

    b2World physicalWorld = b2World(b2Vec2(0.0f, gravityOnY));
    //b2World physicalWorld = b2World(b2Vec2(0.0f, 0));
    b2Body* ballBody;

    void createSprites();
    void touchingEnemy();
    void touchingToLower();
    void touchingToUpper();
    void touchingBonus(sf::Vector2i);
    void finishLevel();
    void createBall(float radius = sizeOfBlockInMeters / 2.0f - sizeOfBlockInMeters / 100.0f);
    void createBall(b2Vec2 position, float radius = sizeOfBlockInMeters / 2.0f - sizeOfBlockInMeters / 100.0f);
    sf::Vector2i findBorder(unsigned int border, sf::Vector2i start, sf::Vector2i end, sf::Vector2i step);

public:
    World(Level level, unsigned int width, unsigned int height);

    sf::Vector2f getMainObjectPosition();

    sf::Vector2f update(long long elapsedTime);
    void input(sf::Keyboard::Key addPowerVector);
    void drawTexture(sf::RenderWindow& worldWindows);

    bool isFinish();

};


#endif //BOUNCE_WORLD_H
