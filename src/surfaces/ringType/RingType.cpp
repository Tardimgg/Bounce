//
// Created by oop on 30.11.2021.
//

#include "../../../headers/surfaces/ringType/RingType.h"

RingType::RingType(const std::string &path) : Surface(path) {

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

