//
// Created by oop on 13.11.2021.
//

#ifndef BOUNCE_LEVEL_H
#define BOUNCE_LEVEL_H


#include <string>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>

enum LevelItem{
    BRICK, TORCH, NULL_VALUE, BALL
};

class Level {


private:
    int width;
    int height;
    int** levelMap;
    std::unordered_map<int, LevelItem> idItems;
    std::unordered_map<LevelItem, std::string> pathToImage;

public:
    Level(const std::string& path);

    int getWidth();
    int getHeigth();

    int** getData();

    LevelItem getLevelItemById(int id);
    std::string getImagePathByItemType(LevelItem item);

};




#endif //BOUNCE_LEVEL_H
