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

    tinyxml2::XMLElement* layerElement = mapInfo->FirstChildElement("layer");
    this->idItems.insert(std::pair<int, LevelItem>(1, BRICK));

    tinyxml2::XMLElement* data = layerElement->FirstChildElement("data");
    std::string map = data->GetText();

    this->levelMap = (int **) malloc(this->height * sizeof(int *));
    for (int i = 0; i < this->height; ++i) {
        this->levelMap[i] = (int *) malloc(this->width * sizeof(int));
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
            this->levelMap[y][x++] = value - '0';
        }
    }
}

int Level::getWidth() {
    return this->width;
}

int Level::getHeigth() {
    return this->height;
}

int** Level::getData() {
    return levelMap;
}

LevelItem Level::getLevelItemById(int id) {
    if (this->idItems.find(id) == this->idItems.end()) {
        return NULL_VALUE;
    }
    return this->idItems[id];
}

std::string Level::getImagePathByItemType(LevelItem item) {
    if (this->pathToImage.find(item) == this->pathToImage.end()) {
        return "";
    }
    return this->pathToImage[item];
}


