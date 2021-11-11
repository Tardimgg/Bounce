//
// Created by oop on 03.11.2021.
//

#include "../headers/View.h"

View::View(const std::string &path) : Environment(path) {

}

sf::Vector2f View::getPosition() {
    return this->position;
}

void View::setPosition(float width, float height) {
    this->position.x = width;
    this->position.y = height;
}

void View::setPosition(sf::Vector2f newPosition) {
    this->position = newPosition;
}
