//
// Created by oop on 25.11.2021.
//

#include "../../headers/surfaces/Ring.h"

Ring::Ring(const std::string &path, float size) : Surface(path) {
    float halfBlockSize = size / 2;
    float widthSpike = halfBlockSize * (126.0f / 272);

    float coef = (1.0f / 10);

    this->upperRing.emplace_back(-widthSpike, -halfBlockSize);
    this->upperRing.emplace_back(widthSpike, -halfBlockSize);
    this->upperRing.emplace_back(widthSpike, -halfBlockSize * coef);
    this->upperRing.emplace_back(-widthSpike, -halfBlockSize * coef);

    this->lowerRing.emplace_back(-widthSpike, size + halfBlockSize * coef);
    this->lowerRing.emplace_back(widthSpike, size + halfBlockSize * coef);
    this->lowerRing.emplace_back(widthSpike, size + halfBlockSize);
    this->lowerRing.emplace_back(-widthSpike, size + halfBlockSize);

    for (int i = 0; i < 4; ++i) {
        Surface::addPoint(this->upperRing[i]);
    }
}

b2Fixture *Ring::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    Surface::buildOnEngineWithoutTop(world, x, y);

    Surface::clearPoints();

    for (int i = 0; i < 4; ++i) {
        Surface::addPoint(this->lowerRing[i]);
    }

    return Surface::buildOnEngineWithoutTop(world, x, y);
}


