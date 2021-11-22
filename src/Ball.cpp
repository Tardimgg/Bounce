//
// Created by oop on 03.11.2021.
//

#include "../headers/Ball.h"

Ball::Ball(const std::string &path) : View(path) {
    this->getTexture().setSmooth(true);
}