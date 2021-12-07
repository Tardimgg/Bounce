//
// Created by oop on 25.11.2021.
//

#include "../../../headers/surfaces/ringType/Ring.h"

Ring::Ring(const std::string &path, float size) : RingType(path) {
    float halfBlockSize = size / 2;
    float widthRing = halfBlockSize * (126.0f / 272);

    float coef = (1.0f / 800);

    this->addFirstPoint(-widthRing, -halfBlockSize);
    this->addFirstPoint(widthRing, -halfBlockSize);
    this->addFirstPoint(0, -halfBlockSize * coef);

    this->addSecondPoint(0, size + halfBlockSize * coef);
    this->addSecondPoint(widthRing, size + halfBlockSize);
    this->addSecondPoint(-widthRing, size + halfBlockSize);

}

b2Fixture *Ring::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    return buildOnEngine(world, x, y).first;
}

std::pair<b2Fixture *, b2Fixture *> Ring::buildOnEngine(b2World &world, float x, float y) {
    std::pair<b2Fixture*, b2Fixture*> fixture = RingType::buildOnEngine(world, x, y);
    fixture.first->GetUserData().pointer = ORDINARY_RING_TYPE;
    fixture.second->GetUserData().pointer = ORDINARY_RING_TYPE;

    return {fixture.first, fixture.second};
}
