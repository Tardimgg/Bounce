//
// Created by oop on 30.11.2021.
//

#include "../../../headers/surfaces/ringType/RotatedBigRing.h"


RotatedBigRing::RotatedBigRing(const std::string &path, float size) : RotatedRingType(path) {
    float halfBlockSize = size / 2;
    float widthRing = halfBlockSize * (126.0f / 272);

    float coef = (2.0f / 500);

    this->addFirstPoint(-halfBlockSize, -widthRing);
    this->addFirstPoint(-halfBlockSize * coef, 0);
    this->addFirstPoint(-halfBlockSize, widthRing);

    this->addSecondPoint(size + halfBlockSize, -widthRing);
    this->addSecondPoint(size + halfBlockSize, widthRing);
    this->addSecondPoint(size + halfBlockSize * coef, 0);
}

b2Fixture *RotatedBigRing::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    return buildOnEngine(world, x, y).first;

}

std::pair<b2Fixture *, b2Fixture *> RotatedBigRing::buildOnEngine(b2World &world, float x, float y) {
    std::pair<b2Fixture*, b2Fixture*> fixture = RingType::buildOnEngine(world, x, y);
    fixture.first->GetUserData().pointer = ROTATED_BIG_RING_TYPE;
    fixture.second->GetUserData().pointer = ROTATED_BIG_RING_TYPE;

    return {fixture.first, fixture.second};
}