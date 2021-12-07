//
// Created by oop on 30.11.2021.
//

#include "../headers/Spider.h"

Spider::Spider( b2Vec2 startPosition, b2Vec2 stopPosition, b2Vec2 moving, float side) :
        startPosition(startPosition),
        stopPosition(stopPosition),
        movement(moving){

    this->points.emplace_back(-side, -side);
    this->points.emplace_back(side, -side);
    this->points.emplace_back(side, side);
    this->points.emplace_back(-side, side);

}

std::pair<b2Body *, b2Fixture *> Spider::buildOnEngine(b2World &world) {
    return this->buildOnEngine(world, this->startPosition.x, this->startPosition.y);
}


std::pair<b2Body *, b2Fixture *> Spider::buildOnEngine(b2World &world, float x, float y) {
    b2BodyDef spiderBodyDef;
    spiderBodyDef.type = b2_dynamicBody;
    spiderBodyDef.position.Set(x, y);
    b2Body *spiderBody = world.CreateBody(&spiderBodyDef);

    b2PolygonShape groundBox;
    groundBox.Set(&this->points[0], (int32) this->points.size());

    b2Fixture* fixture = spiderBody->CreateFixture(&groundBox, 0.0f);
    fixture->GetUserData().pointer = ENEMY;
    //fixture->SetRestitution(1);

    return {spiderBody, fixture};
}

FlyingView* Spider::getView() {
    return Spider::view;
}

FlyingView* Spider::view = nullptr;


void Spider::initView(const std::string& path) {
    Spider::view = new FlyingView(path);
}

b2Vec2 Spider::getMoving() {
    b2Vec2 vec = this->movement;
    vec *= (this->moveToEnd ? 1.0f : -1.0f);
    return vec;
}

void Spider::setPosition(b2Vec2 position) {

    if (this->moveToEnd && (this->startPosition - position).Length() >= (this->stopPosition - this->startPosition).Length()) {
        this->moveToEnd = false;
    } else if (!this->moveToEnd && (this->stopPosition - position).Length() >= (this->stopPosition - this->startPosition).Length()) {
        this->moveToEnd = true;
    }
}

