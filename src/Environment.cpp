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
