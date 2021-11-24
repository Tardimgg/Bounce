//
// Created by oop on 03.11.2021.
//

#include "../headers/FlyingView.h"

FlyingView::FlyingView(const std::string &path) : Environment(path) {

}

sf::Vector2f FlyingView::getPosition() {
    return this->position;
}

void FlyingView::setPosition(float width, float height) {
    this->position.x = width;
    this->position.y = height;
}

void FlyingView::setPosition(sf::Vector2f newPosition) {
    this->position = newPosition;
}

void FlyingView::buildSprite(float scaleCoefOX, float scaleCoefOY) {
    Environment::buildSprite(scaleCoefOX, scaleCoefOY);

    sf::Vector2u ballSize = Environment::getTexture().getSize();
    Environment::getSprite()->setOrigin((float) ballSize.x / 2, (float) ballSize.y / 2);
}
