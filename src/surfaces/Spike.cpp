//
// Created by oop on 03.11.2021.
//

#include "../../headers/surfaces/Spike.h"
#include "../../headers/Level.h"

Spike::Spike(const std::string &path, float size) : Surface(path) {
    float halfBlockSize = size / 2;
    float widthSpike = halfBlockSize * (126.0f / 272);

    Surface::addPoint(-widthSpike, -halfBlockSize);
    Surface::addPoint(widthSpike, -halfBlockSize);
    Surface::addPoint(widthSpike, halfBlockSize);
    Surface::addPoint(-widthSpike, halfBlockSize);
}

b2Fixture* Spike::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    b2Fixture* fixture = Surface::buildOnEngineWithoutTop(world, x, y);
    fixture->GetUserData().pointer = ENEMY;
    return fixture;
}

std::pair<b2Fixture *, b2Fixture *> Spike::buildOnEngine(b2World &world, float x, float y) {
    return {Spike::buildOnEngineWithoutTop(world, x, y), nullptr};
}

