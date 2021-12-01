//
// Created by oop on 30.11.2021.
//

#include "../../headers/surfaces/JumpBlock.h"

JumpBlock::JumpBlock(const std::string &path, float size) : Block(path, size) {

}

std::pair<b2Fixture *, b2Fixture *> JumpBlock::buildOnEngine(b2World &world, float x, float y) {
    std::pair<b2Fixture*, b2Fixture*> result = Block::buildOnEngine(world, x, y);
    result.second->SetRestitution(1.2f);

    return result;
}

