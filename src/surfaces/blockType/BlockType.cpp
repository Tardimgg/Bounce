//
// Created by oop on 30.11.2021.
//

#include "../../../headers/surfaces/blockType/BlockType.h"

BlockType::BlockType(const std::string &path) : Surface(path) {

}


b2Fixture *BlockType::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    b2Fixture* fixture = Surface::buildOnEngineWithoutTop(world, x, y);

    fixture->SetFriction(0);
    fixture->SetRestitution(0.3f);
    fixture->GetUserData().pointer = NO_ENEMY;

    return fixture;
}

std::pair<b2Fixture *, b2Fixture *> BlockType::buildOnEngine(b2World &world, float x, float y) {
    std::pair<b2Fixture *, b2Fixture *> pairFixture = Surface::buildOnEngine(world, x, y);

    b2Fixture* topSurface = pairFixture.second;

    topSurface->SetRestitution(0.2f);
    topSurface->SetFriction(100.0f);
    topSurface->GetUserData().pointer = NO_ENEMY;

    return pairFixture;
}