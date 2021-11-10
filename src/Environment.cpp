//
// Created by oop on 03.11.2021.
//

#include "../headers/Environment.h"

Environment::Environment(std::string path) {
    image.loadFromFile(path);
    texture.loadFromImage(image);
    this->sprite.setTexture(texture);

}

sf::Sprite Environment::getSprite() {
    return this->sprite;
}
