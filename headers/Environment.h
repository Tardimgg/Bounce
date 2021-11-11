//
// Created by oop on 03.11.2021.
//

#ifndef BOUNCE_ENVIRONMENT_H
#define BOUNCE_ENVIRONMENT_H

#include <SFML/Graphics.hpp>
#include <string>

class Environment {

private:
    sf::Image image;
    sf::Texture texture;

public:

    explicit Environment(const std::string& path);

    sf::Texture& getTexture();

};


#endif //BOUNCE_ENVIRONMENT_H
