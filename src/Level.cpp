//
// Created by oop on 13.11.2021.
//

#include "../headers/Level.h"
#include "../include/tinyxml2/tinyxml2.h"
#include <iostream>


Level::Level(const std::string& path) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(path.c_str())) {
        std::cout << "Loading level " << path << " failed" << std::endl;
    }

    tinyxml2::XMLElement* mapInfo = doc.FirstChildElement("map");
    this->width = atoi(mapInfo->Attribute("width"));
    this->height = atoi(mapInfo->Attribute("height"));

    tinyxml2::XMLElement* tileSetElement = mapInfo->FirstChildElement("tileset");
    std::string brickPath = tileSetElement->Attribute("source");
    this->pathToImage.insert(std::pair<LevelItem, std::string>(BRICK, brickPath));
    this->pathToImage.insert(std::pair<LevelItem, std::string>(BALL, "../data/newBall.png"));
    this->pathToImage.insert(std::pair<LevelItem, std::string>(SPIKE, "../data/spikeWithBelly.png"));
    this->pathToImage.insert(std::pair<LevelItem, std::string>(RING, "../data/ring.png"));

    tinyxml2::XMLElement* layerElement = mapInfo->FirstChildElement("layer");

    tinyxml2::XMLElement* data = layerElement->FirstChildElement("data");
    std::string map = data->GetText();

    this->levelMap = (LevelItem **) malloc(this->height * sizeof(LevelItem *));
    for (int i = 0; i < this->height; ++i) {
        this->levelMap[i] = (LevelItem *) malloc(this->width * sizeof(LevelItem));
    }

    int x = 0;
    int y = 0;
    for (char value : map) {
        if (value == '\n') {
            if (x != 0) {
                ++y;
                x ^= x;
            }
        } else if (value != ','){
            this->levelMap[y][x++] = Level::idItems[value];
        }
    }
}

std::unordered_map<char, LevelItem> Level::idItems = {
        {'0', AIR},
        {'1', BRICK},
        {'2', SPIKE},
        {'3', RING}
};

int Level::getWidth() {
    return this->width;
}

int Level::getHeight() {
    return this->height;
}

LevelItem** Level::getData() {
    return this->levelMap;
}

std::string Level::getImagePathByItemType(LevelItem item) {
    if (this->pathToImage.find(item) == this->pathToImage.end()) {
        return "";
    }
    return this->pathToImage[item];
}

b2Vec2 Level::getStartPosition() {
    return {2, 2};
}

int Level::getNumberLives() {
    return 3;
}


