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
    sf::Sprite sprite;

public:

    Environment(std::string path);

    sf::Sprite getSprite();

};


#endif //BOUNCE_ENVIRONMENT_H
