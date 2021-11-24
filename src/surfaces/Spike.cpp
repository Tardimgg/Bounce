//
// Created by oop on 03.11.2021.
//

#include "../../headers/surfaces/Spike.h"

Spike::Spike(const std::string &path, float size) : Surface(path) {
    float halfBlockSize = size / 2;
    float widthSpike = halfBlockSize * (126.0f / 272);

    Surface::addPoint(-widthSpike, -halfBlockSize);
    Surface::addPoint(widthSpike, -halfBlockSize);
    Surface::addPoint(widthSpike, halfBlockSize);
    Surface::addPoint(-widthSpike, halfBlockSize);
}

