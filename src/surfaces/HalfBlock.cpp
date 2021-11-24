//
// Created by oop on 24.11.2021.
//

#include "../../headers/surfaces/HalfBlock.h"

HalfBlock::HalfBlock(const std::string &path, float size) : Surface(path){
    float halfBlockSize = size / 2;

    Surface::addPoint(-halfBlockSize, -halfBlockSize + 0.1f);
    Surface::addPoint(halfBlockSize, halfBlockSize + 0.1f);
    Surface::addPoint(-halfBlockSize, halfBlockSize);
    Surface::addTopPoint(-halfBlockSize, -halfBlockSize);
    Surface::addTopPoint(halfBlockSize, halfBlockSize);
}
