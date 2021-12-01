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


enum LevelItem : unsigned int {
    BRICK                    = 1 << 0,
    LEFT_HALF_BRICK          = 1 << 1,
    RIGHT_HALF_BRICK         = 1 << 2,
    TOP_LEFT_HALF_BLOCK      = 1 << 3,
    TOP_RIGHT_HALF_BLOCK     = 1 << 4,
    SPIKE                    = 1 << 5,
    FLY_ENEMY                = 1 << 6,
    AIR                      = 1 << 7,
    WATER                    = 1 << 8,
    BALL                     = 1 << 9,
    BIG_BALL                 = 1 << 10,
    RING                     = 1 << 11,
    VISITED_RING             = 1 << 12,
    ROTATED_RING             = 1 << 13,
    VISITED_ROTATED_RING     = 1 << 14,
    CLOSE_END_LEVEL          = 1 << 15,
    END_LEVEL                = 1 << 16,
    TO_LOWER_ITEM            = 1 << 17,
    TO_UPPER_ITEM            = 1 << 18,
    BIG_RING                 = 1 << 19,
    ROTATED_BIG_RING         = 1 << 10,
    VISITED_BIG_RING         = 1 << 21,
    VISITED_ROTATED_BIG_RING = 1 << 22,
    OX_SPIDER                = 1 << 23,
    OY_SPIDER                = 1 << 24,
    JUMP_BRICK               = 1 << 25,

};

enum TypeFigure{
    ERROR                  = 0,
    ENEMY                  = 1 << 0,
    NO_ENEMY               = 1 << 1,
    BONUS                  = 1 << 2,
    ORDINARY_RING_TYPE     = 1 << 3,
    ROTATED_RING_TYPE      = 1 << 4,
    END_LEVEL_TYPE         = 1 << 5,
    TO_LOWER_ITEM_TYPE     = 1 << 6,
    TO_UPPER_ITEM_TYPE     = 1 << 7,
    ORDINARY_BIG_RING_TYPE = 1 << 8,
    ROTATED_BIG_RING_TYPE  = 1 << 9,
    BALL_TYPE              = 1 << 10,


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
