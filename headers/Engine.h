//
// Created by oop on 09.11.2021.
//

#ifndef BOUNCE_ENGINE_H
#define BOUNCE_ENGINE_H

#include <SFML/Graphics.hpp>
#include "World.h"

class Engine {

private:

    sf::RenderWindow window;
    World world;
    sf::Vector2u resolution;
    sf::Vector2i position;

    sf::View* viewWindow;

    void input();
    void update(int elapsed);
    void draw();

public:
    Engine();

    void start();

};


#endif //BOUNCE_ENGINE_H
