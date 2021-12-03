//
// Created by oop on 30.11.2021.
//

#include "../../../headers/surfaces/ringType/BigRing.h"


BigRing::BigRing(const std::string &path, float size) : RingType(path) {
    float halfBlockSize = size / 2;
    float widthRing = halfBlockSize * (126.0f / 272);

    float coef = (4.0f / 10);

    this->upperRing.emplace_back(-widthRing, -halfBlockSize);
    this->upperRing.emplace_back(widthRing, -halfBlockSize);
    this->upperRing.emplace_back(0, -halfBlockSize * coef);

    this->lowerRing.emplace_back(0, size + halfBlockSize * coef);
    this->lowerRing.emplace_back(widthRing, size + halfBlockSize);
    this->lowerRing.emplace_back(-widthRing, size + halfBlockSize);

    for (int i = 0; i < this->upperRing.size(); ++i) {
        Surface::addPoint(this->upperRing[i]);
    }
}

b2Fixture *BigRing::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    b2Fixture* topFixture = Surface::buildOnEngineWithoutTop(world, x, y);
    topFixture->GetUserData().pointer = ORDINARY_BIG_RING_TYPE;

    Surface::clearPoints();
    for (int i = 0; i < this->lowerRing.size(); ++i) {
        Surface::addPoint(this->lowerRing[i]);
    }

    b2Fixture* lowerFixture = Surface::buildOnEngineWithoutTop(world, x, y);
    lowerFixture->GetUserData().pointer = ORDINARY_BIG_RING_TYPE;

    Surface::clearPoints();
    for (int i = 0; i < this->upperRing.size(); ++i) {
        Surface::addPoint(this->upperRing[i]);
    }

    return lowerFixture;
}

std::pair<b2Fixture *, b2Fixture *> BigRing::buildOnEngine(b2World &world, float x, float y) {
    return {BigRing::buildOnEngineWithoutTop(world, x, y), nullptr};
}
