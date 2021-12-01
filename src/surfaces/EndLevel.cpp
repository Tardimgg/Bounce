//
// Created by oop on 27.11.2021.
//

#include "../../headers/surfaces/EndLevel.h"
#include "../../headers/Level.h"

EndLevel::EndLevel(const std::string &path, float size) : Surface(path) {
    float halfBlockSize = size / 2;
    //float widthEndLevel = halfBlockSize * (1.0f / 3);
    float widthEndLevel = 1;


    Surface::addPoint(-halfBlockSize * widthEndLevel, -halfBlockSize);
    Surface::addPoint(size + halfBlockSize * widthEndLevel, -halfBlockSize);
    Surface::addPoint(size + halfBlockSize * widthEndLevel, size + halfBlockSize);
    Surface::addPoint(-halfBlockSize * widthEndLevel, size + halfBlockSize);
}

b2Fixture *EndLevel::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    b2Fixture* fixture = Surface::buildOnEngineWithoutTop(world, x, y);

    fixture->GetUserData().pointer = END_LEVEL_TYPE;

    return fixture;
}

std::pair<b2Fixture *, b2Fixture *> EndLevel::buildOnEngine(b2World &world, float x, float y) {
    return {EndLevel::buildOnEngineWithoutTop(world, x, y), nullptr};
}

