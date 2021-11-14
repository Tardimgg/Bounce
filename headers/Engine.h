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
    World* world;
    sf::Vector2f positionCamera{0, 0};
    bool mainObjectInNormalXPosition = false;
    bool mainObjectInNormalYPosition = false;

    sf::View* viewWindow;

    void input();
    void update(long long elapsedTime);
    void draw();

public:
    Engine();

    void start();

};


#endif //BOUNCE_ENGINE_H
