//
// Created by oop on 30.11.2021.
//

#include "../../headers/surfaces/Magnifier.h"

Magnifier::Magnifier(const std::string &path, float size) : Surface(path) {
    float halfBlockSize = size / 2;
    float widthMagnifier = halfBlockSize * (122.0f / 272);


    Surface::addPoint(-widthMagnifier, -halfBlockSize);
    Surface::addPoint(widthMagnifier, -halfBlockSize);
    Surface::addPoint(widthMagnifier, halfBlockSize);
    Surface::addPoint(-widthMagnifier, halfBlockSize);
}

b2Fixture *Magnifier::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    b2Fixture* fixture = Surface::buildOnEngineWithoutTop(world, x, y);

    fixture->SetFriction(100.0f);
    fixture->SetRestitution(0.3f);
    fixture->GetUserData().pointer = TO_UPPER_ITEM_TYPE;

    return fixture;
}

std::pair<b2Fixture *, b2Fixture *> Magnifier::buildOnEngine(b2World &world, float x, float y) {
    return {Magnifier::buildOnEngineWithoutTop(world, x, y), nullptr};

}