//
// Created by oop on 30.11.2021.
//

#include "../../headers/surfaces/Diminutive.h"

Diminutive::Diminutive(const std::string &path, float size) : Surface(path) {
    float halfBlockSize = size / 2;

    Surface::addPoint(-halfBlockSize, -halfBlockSize);
    Surface::addPoint(halfBlockSize, -halfBlockSize);
    Surface::addPoint(halfBlockSize, halfBlockSize);
    Surface::addPoint(-halfBlockSize, halfBlockSize);
}

b2Fixture *Diminutive::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    b2Fixture* fixture = Surface::buildOnEngineWithoutTop(world, x, y);

    fixture->SetFriction(100.0f);
    fixture->SetRestitution(0.3f);
    fixture->GetUserData().pointer = TO_LOWER_ITEM_TYPE;

    return fixture;
}

std::pair<b2Fixture *, b2Fixture *> Diminutive::buildOnEngine(b2World &world, float x, float y) {
    return {Diminutive::buildOnEngineWithoutTop(world, x, y), nullptr};

}