//
// Created by oop on 30.11.2021.
//

#include "../../../headers/surfaces/ringType/RotatedRingType.h"

RotatedRingType::RotatedRingType(const std::string &path) : RingType(path) {

}

void RotatedRingType::selectFirstHalfToDisplay() {
    sf::Vector2u size = Environment::getTexture().getSize();
    Environment::getSprite()->setTextureRect(sf::IntRect(0, 0, (int) size.x, (int) size.y >> 1));
}

void RotatedRingType::selectSecondHalfToDisplay() {
    sf::Vector2u size = Environment::getTexture().getSize();
    Environment::getSprite()->setTextureRect(sf::IntRect(0, (int) size.y >> 1, (int) size.x, (int) size.y));
}

void RotatedRingType::selectAllRingToDisplay() {
    sf::Vector2u size = Environment::getTexture().getSize();
    Environment::getSprite()->setTextureRect(sf::IntRect(0, 0, (int) size.x, (int) size.y));
}

