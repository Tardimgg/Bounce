//
// Created by oop on 26.11.2021.
//

#include "../../../headers/surfaces/ringType/RotatedRing.h"

RotatedRing::RotatedRing(const std::string &path, float size) : RotatedRingType(path) {
    float halfBlockSize = size / 2;
    float widthRing = halfBlockSize * (126.0f / 272);

    float coef = (1.0f / 800);

    this->addFirstPoint(-halfBlockSize, -widthRing);
    this->addFirstPoint(-halfBlockSize * coef, 0);
    this->addFirstPoint(-halfBlockSize, widthRing);

    this->addSecondPoint(size + halfBlockSize, -widthRing);
    this->addSecondPoint(size + halfBlockSize, widthRing);
    this->addSecondPoint(size + halfBlockSize * coef, 0);

}

b2Fixture *RotatedRing::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    return buildOnEngine(world, x, y).first;
}

std::pair<b2Fixture *, b2Fixture *> RotatedRing::buildOnEngine(b2World &world, float x, float y) {
    std::pair<b2Fixture*, b2Fixture*> fixture = RingType::buildOnEngine(world, x, y);
    fixture.first->GetUserData().pointer = ROTATED_RING_TYPE;
    fixture.second->GetUserData().pointer = ROTATED_RING_TYPE;

    return {fixture.first, fixture.second};
}