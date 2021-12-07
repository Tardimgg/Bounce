//
// Created by oop on 30.11.2021.
//

#include "../../../headers/surfaces/ringType/BigRing.h"


BigRing::BigRing(const std::string &path, float size) : RingType(path) {
    float halfBlockSize = size / 2;
    float widthRing = halfBlockSize * (126.0f / 272);

    float coef = (4.0f / 10);

    this->addFirstPoint(-widthRing, -halfBlockSize);
    this->addFirstPoint(widthRing, -halfBlockSize);
    this->addFirstPoint(0, -halfBlockSize * coef);

    this->addSecondPoint(0, size + halfBlockSize * coef);
    this->addSecondPoint(widthRing, size + halfBlockSize);
    this->addSecondPoint(-widthRing, size + halfBlockSize);

}

b2Fixture *BigRing::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    return buildOnEngine(world, x, y).first;

}

std::pair<b2Fixture *, b2Fixture *> BigRing::buildOnEngine(b2World &world, float x, float y) {
    std::pair<b2Fixture*, b2Fixture*> fixture = RingType::buildOnEngine(world, x, y);
    fixture.first->GetUserData().pointer = ORDINARY_BIG_RING_TYPE;
    fixture.second->GetUserData().pointer = ORDINARY_BIG_RING_TYPE;

    return {fixture.first, fixture.second};
}
