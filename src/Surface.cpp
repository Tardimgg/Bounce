//
// Created by oop on 19.11.2021.
//

#include "../headers/Surface.h"

Surface::Surface(const std::string &path) : Environment(path) {
    this->localIndex = ++numberObjectsCreated;
    Surface::globalPoints.insert(std::pair<int, std::vector<b2Vec2>>(this->localIndex, std::vector<b2Vec2>()));
}

int Surface::numberObjectsCreated = 0;
std::unordered_map<int, std::vector<b2Vec2>> Surface::globalPoints;

void Surface::addPoint(float x, float y) {
    Surface::globalPoints[this->localIndex].push_back(b2Vec2(x, y));
}

std::vector<b2Vec2> Surface::getPoints() {
    return Surface::globalPoints[this->localIndex];
}
