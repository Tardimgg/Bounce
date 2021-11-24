//
// Created by oop on 19.11.2021.
//

#include "../../headers/surfaces/Surface.h"

Surface::Surface(const std::string &path) : Environment(path) {
    this->localIndex = ++numberObjectsCreated;
    Surface::globalPoints.insert(std::pair<int, std::vector<b2Vec2>>(this->localIndex, std::vector<b2Vec2>()));
    Surface::globalTopPoints.insert(std::pair<int, std::vector<b2Vec2>>(this->localIndex, std::vector<b2Vec2>()));
}

int Surface::numberObjectsCreated = 0;
std::unordered_map<int, std::vector<b2Vec2>> Surface::globalPoints;
std::unordered_map<int, std::vector<b2Vec2>> Surface::globalTopPoints;

void Surface::addPoint(float x, float y) {
    Surface::globalPoints[this->localIndex].push_back(b2Vec2(x, y));
}

void Surface::addPoint(b2Vec2 vec) {
    Surface::globalPoints[this->localIndex].push_back(vec);
}

void Surface::addTopPoint(float x, float y) {
    Surface::globalTopPoints[this->localIndex].push_back(b2Vec2(x, y));
}

void Surface::addTopPoint(b2Vec2 vec) {
    Surface::globalTopPoints[this->localIndex].push_back(vec);
}


void Surface::clearPoints() {
    Surface::globalPoints[this->localIndex].clear();
}

std::vector<b2Vec2> Surface::getPoints() {
    return Surface::globalPoints[this->localIndex];
}

std::vector<b2Vec2> Surface::getTopPoints() {
    return Surface::globalTopPoints[this->localIndex];

}

b2Fixture* Surface::buildOnEngineWithoutTop(b2World& world, float x, float y) {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(x, y);
    b2Body *groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;

    std::vector<b2Vec2> points = this->getPoints();
    groundBox.Set(&points[0], (int32) points.size());

    return groundBody->CreateFixture(&groundBox, 0.0f);
}

std::pair<b2Fixture *, b2Fixture *> Surface::buildOnEngine(b2World &world, float x, float y) {
    b2Fixture* mainFixture = buildOnEngineWithoutTop(world, x, y);

    b2BodyDef edgeBodyDef;
    edgeBodyDef.position.Set(x, y);
    b2Body *edgeBody = world.CreateBody(&edgeBodyDef);

    b2EdgeShape edgeShape;
    std::vector<b2Vec2> topPoints = this->getTopPoints();

    edgeShape.SetTwoSided({topPoints[0].x, topPoints[0].y},
                          {topPoints[1].x, topPoints[1].y}
    );

    return {mainFixture, edgeBody->CreateFixture(&edgeShape, 0.0f)};
}


