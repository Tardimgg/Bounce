//
// Created by oop on 30.11.2021.
//

#ifndef BOUNCE_BLOCKTYPE_H
#define BOUNCE_BLOCKTYPE_H

#include "../Surface.h"
#include "../../Level.h"


class BlockType : public Surface {

public:

    explicit BlockType(const std::string &path);

    b2Fixture* buildOnEngineWithoutTop(b2World& world, float x, float y) override;
    std::pair<b2Fixture*, b2Fixture*> buildOnEngine(b2World& world, float x, float y) override;

};


#endif //BOUNCE_BLOCKTYPE_H
