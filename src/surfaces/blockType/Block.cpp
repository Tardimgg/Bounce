//
// Created by oop on 03.11.2021.
//

#include "../../../headers/surfaces/blockType/Block.h"

Block::Block(const std::string &path, float size) : BlockType(path) {
    float halfBlockSize = size / 2;

    Surface::addPoint(-halfBlockSize, -halfBlockSize + 0.1f);
    Surface::addPoint(halfBlockSize, -halfBlockSize + 0.1f);
    Surface::addPoint(halfBlockSize, halfBlockSize);
    Surface::addPoint(-halfBlockSize, halfBlockSize);


    Surface::addTopPoint(-halfBlockSize, -halfBlockSize);
    Surface::addTopPoint(halfBlockSize, -halfBlockSize);
}