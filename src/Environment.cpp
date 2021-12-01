//
// Created by oop on 03.11.2021.
//

#include "../headers/Environment.h"

Environment::Environment(const std::string& path) {
    this->image.loadFromFile(path);
    this->texture.loadFromImage(image);

}

sf::Texture& Environment::getTexture() {
    return this->texture;
}

void Environment::buildSprite(float scaleCoefOX, float scaleCoefOY) {
    sf::Vector2u size = this->texture.getSize();

    sf::Vector2f scaleCoef(scaleCoefOX, scaleCoefOY);

    this->sprite.setTexture(this->getTexture());
    this->sprite.setScale(scaleCoef);
    this->sprite.setTextureRect(sf::IntRect(0, 0, (int) size.x, (int) size.y));
}

sf::Sprite* Environment::getSprite(){
    return &sprite;
}
