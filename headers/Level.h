//
// Created by oop on 13.11.2021.
//

#ifndef BOUNCE_LEVEL_H
#define BOUNCE_LEVEL_H


#include <string>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include "../include/box2d/b2_math.h"
#include <sstream>
#include "../include/tinyxml2/tinyxml2.h"
#include <iostream>


enum LevelItem : unsigned int {
    BRICK                    = 1 << 0,
    LEFT_HALF_BRICK          = 1 << 1,
    RIGHT_HALF_BRICK         = 1 << 2,
    TOP_LEFT_HALF_BRICK      = 1 << 3,
    TOP_RIGHT_HALF_BRICK     = 1 << 4,
    SPIKE                    = 1 << 5,
    AIR                      = 1 << 6,
    BALL                     = 1 << 7,
    RING                     = 1 << 8,
    VISITED_RING             = 1 << 9,
    ROTATED_RING             = 1 << 10,
    VISITED_ROTATED_RING     = 1 << 11,
    CLOSE_END_LEVEL          = 1 << 12,
    END_LEVEL                = 1 << 13,
    TO_LOWER_ITEM            = 1 << 14,
    TO_UPPER_ITEM            = 1 << 15,
    BIG_RING                 = 1 << 16,
    ROTATED_BIG_RING         = 1 << 17,
    VISITED_BIG_RING         = 1 << 18,
    VISITED_ROTATED_BIG_RING = 1 << 19,
    OX_SPIDER                = 1 << 20,
    OY_SPIDER                = 1 << 21,
    JUMP_BRICK               = 1 << 22,
};

enum TypeFigure{
    ENEMY                  = 1 << 0,
    NO_ENEMY               = 1 << 1,
    ORDINARY_RING_TYPE     = 1 << 2,
    ROTATED_RING_TYPE      = 1 << 3,
    END_LEVEL_TYPE         = 1 << 4,
    TO_LOWER_ITEM_TYPE     = 1 << 5,
    TO_UPPER_ITEM_TYPE     = 1 << 6,
    ORDINARY_BIG_RING_TYPE = 1 << 7,
    ROTATED_BIG_RING_TYPE  = 1 << 8,
    BALL_TYPE              = 1 << 9,

};


class Level {


private:

    int startX;
    int startY;

    int countRing = 0;

    int width;
    int height;
    LevelItem** levelMap;
    static std::unordered_map<std::string, LevelItem> idItems;
    std::unordered_map<LevelItem, std::string> pathToImage;

public:
    Level(const std::string& path);

    int getWidth();
    int getHeight();

    LevelItem** getData();

    std::string getImagePathByItemType(LevelItem item);

    b2Vec2 getStartPosition();

    int getNumberLives();
    int getNumberRings();

};


#endif //BOUNCE_LEVEL_H
