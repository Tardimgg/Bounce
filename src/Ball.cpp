//
// Created by oop on 03.11.2021.
//

#include "../headers/Ball.h"

Ball::Ball(const std::string &path) : FlyingView(path) {
    this->getTexture().setSmooth(true);
}

std::pair<b2Body *, b2Fixture *> Ball::buildOnEngine(b2World &world, float radius, float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    bodyDef.angularDamping = 0.7f;
    b2Body* ballBody = world.CreateBody(&bodyDef);

    b2CircleShape dynamicBallShape;
    dynamicBallShape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBallShape;
    fixtureDef.density = 1300.0f;

    b2Fixture* fixture = ballBody->CreateFixture(&fixtureDef);
    fixture->GetUserData().pointer = BALL_TYPE;

    return {ballBody, fixture};
}

bool Ball::isSmall() {
    return this->ballIsSmall;
}

void Ball::setSmallSize(bool smallSize) {
    this->ballIsSmall = smallSize;
}
