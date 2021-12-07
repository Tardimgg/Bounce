//
// Created by oop on 13.11.2021.
//

#include "../headers/Level.h"



Level::Level(const std::string& path) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(path.c_str())) {
        std::cout << "Loading level " << path << " failed" << std::endl;
    }

    tinyxml2::XMLElement* mapInfo = doc.FirstChildElement("map");
    this->width = atoi(mapInfo->Attribute("width"));
    this->height = atoi(mapInfo->Attribute("height"));

    this->startX = atoi(mapInfo->Attribute("startX"));
    this->startY = atoi(mapInfo->Attribute("startY"));

    tinyxml2::XMLElement* tileSetElement = mapInfo->FirstChildElement("tileset");

    while(tileSetElement) {
        std::string pathView = tileSetElement->Attribute("source");

        const char* id = tileSetElement->Attribute("firstgid");
        this->pathToImage.insert(std::pair<LevelItem, std::string>(this->idItems[id], pathView));

        tileSetElement = tileSetElement->NextSiblingElement("tileset");
    }

    tinyxml2::XMLElement* layerElement = mapInfo->FirstChildElement("layer");

    tinyxml2::XMLElement* data = layerElement->FirstChildElement("data");
    std::string map = data->GetText();

    this->levelMap = (LevelItem **) malloc(this->height * sizeof(LevelItem *));
    for (int i = 0; i < this->height; ++i) {
        this->levelMap[i] = (LevelItem *) malloc(this->width * sizeof(LevelItem));
    }

    int x = 0;
    int y = 0;

    std::stringstream stream(map);
    std::string parsed;
    while (getline(stream, parsed, ',')) {
        if (x == this->width) {
            ++y;
            x ^= x;
        }

        if (x == 0 && parsed.substr(0,1) == "\n") {
            parsed.erase(parsed.begin(), parsed.begin() + 1);
        }
        if (x == this->width - 1 && parsed.substr(parsed.size() - 1,1) == "\n") {
            parsed.erase(parsed.end() - 1, parsed.end());
        }

        this->levelMap[y][x++] = Level::idItems[parsed];

        if (this->levelMap[y][x - 1] & (RING | ROTATED_RING | BIG_RING | ROTATED_BIG_RING)) {
            ++this->countRing;
        }
    }
}

std::unordered_map<std::string, LevelItem> Level::idItems = {
        {"0", AIR},
        {"1", BRICK},
        {"2", LEFT_HALF_BRICK},
        {"3", RIGHT_HALF_BRICK},
        {"4", SPIKE},
        {"5", RING},
        {"6", ROTATED_RING},
        {"7", VISITED_RING},
        {"8", VISITED_ROTATED_RING},
        {"9", BIG_RING},
        {"10", ROTATED_BIG_RING},
        {"11", VISITED_BIG_RING},
        {"12", VISITED_ROTATED_BIG_RING},
        {"13", CLOSE_END_LEVEL},
        {"14", END_LEVEL},
        {"15", BALL},
	    {"16", TO_LOWER_ITEM},
    	{"17", TO_UPPER_ITEM},
    	{"18", OX_SPIDER},
    	{"19", OY_SPIDER},
    	{"20", JUMP_BRICK},
    	{"21", TOP_LEFT_HALF_BRICK},
    	{"22", TOP_RIGHT_HALF_BRICK}
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
    return {(float) this->startX, (float) this->startY};
}

int Level::getNumberLives() {
    return 3;
}

int Level::getNumberRings() {
    return this->countRing;
}


