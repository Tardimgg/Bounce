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

std::pair<b2Body *, b2Fixture *> Spider::buildOnEngine(b2World &world, float x, float y) {
    b2BodyDef SpiderBodyDef;
    SpiderBodyDef.type = b2_dynamicBody;
    SpiderBodyDef.position.Set(x, y);
    b2Body *spiderBody = world.CreateBody(&SpiderBodyDef);

    b2PolygonShape groundBox;
    groundBox.Set(&this->points[0], (int32) this->points.size());

    b2Fixture* fixture = spiderBody->CreateFixture(&groundBox, 0.0f);
    fixture->GetUserData().pointer = ENEMY;
    //fixture->SetRestitution(1);

    return {spiderBody, fixture};
}

//b2Vec2 Spider::getPosition(long long int timeElapsed) {
//    if (this->movement.y == 0) {
//        timeElapsed %= (long long) (std::abs(this->stopPosition.x - this->startPosition.x) * 2 / this->movement.x);
//        if (this->stopPosition.x + (float) timeElapsed * this->movement.x > this->stopPosition.x) {
//            timeElapsed -= (long) ((this->stopPosition.x - this->currentPosition.x) / this->movement.x);
//            this->currentPosition = this->stopPosition;
//            this->movingToEnd = false;
//        }
//
//        this->currentPosition.x += (this->movingToEnd ? 1.0f : -1.0f) * (this->movement.x) * (float) timeElapsed;
//    }
//
//    if (this->movement.x == 0) {
//        timeElapsed %= (long long) (std::abs(this->stopPosition.y - this->startPosition.y) * 2 / this->movement.y);
//        if (this->stopPosition.y + (float) timeElapsed * this->movement.y > this->stopPosition.y) {
//            timeElapsed -= (long) ((this->stopPosition.y - this->currentPosition.y) / this->movement.y);
//            this->currentPosition = this->stopPosition;
//            this->movingToEnd = false;
//        }
//
//        this->currentPosition.y += (this->movingToEnd ? 1.0f : -1.0f) * (this->movement.y) * (float) timeElapsed;
//    }
//}

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

