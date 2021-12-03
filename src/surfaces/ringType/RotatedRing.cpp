//
// Created by oop on 26.11.2021.
//

#include "../../../headers/surfaces/ringType/RotatedRing.h"

RotatedRing::RotatedRing(const std::string &path, float size) : RotatedRingType(path) {
    float halfBlockSize = size / 2;
    float widthRing = halfBlockSize * (126.0f / 272);

    float coef = (2.0f / 100);

    this->leftRing.emplace_back(-halfBlockSize, -widthRing);
    this->leftRing.emplace_back(-halfBlockSize * coef, 0);
    this->leftRing.emplace_back(-halfBlockSize, widthRing);

    this->rightRing.emplace_back(size + halfBlockSize, -widthRing);
    this->rightRing.emplace_back(size + halfBlockSize, widthRing);
    this->rightRing.emplace_back(size + halfBlockSize * coef, 0);

    for (int i = 0; i < this->leftRing.size(); ++i) {
        Surface::addPoint(this->leftRing[i]);
    }
}

b2Fixture *RotatedRing::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    b2Fixture* topFixture = Surface::buildOnEngineWithoutTop(world, x, y);
    topFixture->GetUserData().pointer = ROTATED_RING_TYPE;

    Surface::clearPoints();
    for (int i = 0; i < this->rightRing.size(); ++i) {
        Surface::addPoint(this->rightRing[i]);
    }

    b2Fixture* lowerFixture = Surface::buildOnEngineWithoutTop(world, x, y);
    lowerFixture->GetUserData().pointer = ROTATED_RING_TYPE;

    Surface::clearPoints();
    for (int i = 0; i < this->leftRing.size(); ++i) {
        Surface::addPoint(this->leftRing[i]);
    }

    return lowerFixture;
}

std::pair<b2Fixture *, b2Fixture *> RotatedRing::buildOnEngine(b2World &world, float x, float y) {
    return {RotatedRing::buildOnEngineWithoutTop(world, x, y), nullptr};
}