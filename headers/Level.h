//
// Created by oop on 13.11.2021.
//

#ifndef BOUNCE_LEVEL_H
#define BOUNCE_LEVEL_H


#include <string>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include "../include/box2d/b2_math.h"

enum LevelItem{
    BRICK      = 1 << 0,
    HALF_BRICK = 1 << 1,
    SPIKE      = 1 << 2,
    FLY_ENEMY  = 1 << 3,
    AIR        = 1 << 4,
    WATER      = 1 << 5,
    BALL       = 1 << 6,
    BIG_BALL   = 1 << 7,
    RING       = 1 << 8
};

enum TypeFigure{
    ENEMY    = 1 << 0,
    NO_ENEMY = 1 << 1
};


class Level {


private:
    int width;
    int height;
    LevelItem** levelMap;
    static std::unordered_map<char, LevelItem> idItems;
    std::unordered_map<LevelItem, std::string> pathToImage;

public:
    Level(const std::string& path);

    int getWidth();
    int getHeight();

    LevelItem** getData();

    std::string getImagePathByItemType(LevelItem item);

    b2Vec2 getStartPosition();

    int getNumberLives();

};




#endif //BOUNCE_LEVEL_H
