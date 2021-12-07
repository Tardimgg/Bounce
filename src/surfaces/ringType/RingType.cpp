//
// Created by oop on 30.11.2021.
//

#include "../../../headers/surfaces/ringType/RingType.h"

RingType::RingType(const std::string &path) : Surface(path) {
    this->localIndex = ++numberObjectsCreated;
    RingType::globalRingPoints.insert(std::pair<int, std::pair<std::vector<b2Vec2>, std::vector<b2Vec2>>>
                                            (this->localIndex, {std::vector<b2Vec2>(), std::vector<b2Vec2>()}));
}

int RingType::numberObjectsCreated = 0;
std::unordered_map<int, std::pair<std::vector<b2Vec2>, std::vector<b2Vec2>>> RingType::globalRingPoints;

void RingType::addFirstPoint(float x, float y) {
    RingType::globalRingPoints[this->localIndex].first.emplace_back(x, y);
}

void RingType::addFirstPoint(b2Vec2 vec) {
    RingType::globalRingPoints[this->localIndex].first.push_back(vec);
}

void RingType::addSecondPoint(float x, float y) {
    RingType::globalRingPoints[this->localIndex].second.emplace_back(x, y);
}

void RingType::addSecondPoint(b2Vec2 vec) {
    RingType::globalRingPoints[this->localIndex].second.push_back(vec);
}

std::pair<std::vector<b2Vec2>, std::vector<b2Vec2>> RingType::getRingPoints() {
    return RingType::globalRingPoints[this->localIndex];
}


b2Fixture *RingType::buildOnEngineWithoutTop(b2World &world, float x, float y) {
    return buildOnEngine(world, x, y).first;
}

std::pair<b2Fixture *, b2Fixture *> RingType::buildOnEngine(b2World &world, float x, float y) {
    std::pair<std::vector<b2Vec2>, std::vector<b2Vec2>> points = this->getRingPoints();

    for (int i = 0; i < points.first.size(); ++i) {
        Surface::addPoint(points.first[i]);
    }

    b2Fixture* firstFixture = Surface::buildOnEngineWithoutTop(world, x, y);

    Surface::clearPoints();
    for (int i = 0; i < points.second.size(); ++i) {
        Surface::addPoint(points.second[i]);
    }

    b2Fixture* secondFixture = Surface::buildOnEngineWithoutTop(world, x, y);
    Surface::clearPoints();

    return {firstFixture, secondFixture};
}

void RingType::selectFirstHalfToDisplay() {
    sf::Vector2u size = Environment::getTexture().getSize();
    Environment::getSprite()->setTextureRect(sf::IntRect(0, 0, (int) size.x >> 1, (int) size.y));
}

void RingType::selectSecondHalfToDisplay() {
    sf::Vector2u size = Environment::getTexture().getSize();
    Environment::getSprite()->setTextureRect(sf::IntRect( (int) size.x >> 1, 0, (int) size.x, (int) size.y));
}

void RingType::selectAllRingToDisplay() {
    sf::Vector2u size = Environment::getTexture().getSize();
    Environment::getSprite()->setTextureRect(sf::IntRect(0, 0, (int) size.x, (int) size.y));

}

