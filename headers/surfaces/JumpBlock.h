//
// Created by oop on 30.11.2021.
//

#ifndef BOUNCE_JUMPBLOCK_H
#define BOUNCE_JUMPBLOCK_H


#include "blockType/Block.h"

class JumpBlock : public Block{

public:

    JumpBlock(const std::string &path, float size);

    std::pair<b2Fixture*, b2Fixture*> buildOnEngine(b2World& world, float x, float y) override;

};


#endif //BOUNCE_JUMPBLOCK_H
