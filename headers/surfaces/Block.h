//
// Created by oop on 03.11.2021.
//

#ifndef BOUNCE_BLOCK_H
#define BOUNCE_BLOCK_H


#include "Surface.h"

class Block : public Surface{

public:

    Block(const std::string &path, float size);

};


#endif //BOUNCE_BLOCK_H
