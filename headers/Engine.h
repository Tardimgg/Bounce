//
// Created by oop on 09.11.2021.
//

#ifndef BOUNCE_ENGINE_H
#define BOUNCE_ENGINE_H

#include <SFML/Graphics.hpp>

class Engine {

private:

    sf::RenderWindow window;

    void input();
    void update(int elapsed);
    void draw();

public:
    Engine();

    void start();

};


#endif //BOUNCE_ENGINE_H
