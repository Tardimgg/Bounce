//
// Created by oop on 03.11.2021.
//

#include "../headers/Ball.h"

Ball::Ball(const std::string &path) : View(path) {

}

sf::Vector2f Ball::getSpeedVector() {
    return this->speedVector;
}

void Ball::setSpeedVector(sf::Vector2f newSpeedVector) {
    this->speedVector = newSpeedVector;
}

void Ball::setSpeedVector(float x, float y) {
    this->speedVector.x = x;
    this->speedVector.y = y;
}
