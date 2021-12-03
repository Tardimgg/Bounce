//
// Created by oop on 09.11.2021.
//

#ifndef BOUNCE_ENGINE_H
#define BOUNCE_ENGINE_H

#include <SFML/Graphics.hpp>
#include "World.h"
#include <stack>
#include <filesystem>

class Engine {

private:

    sf::Image imageWin;
    sf::Texture textureWin;
    sf::Sprite spriteWin;

    sf::Image imageLose;
    sf::Texture textureLose;
    sf::Sprite spriteLose;

    bool gameIsOver = false;
    bool isWin = false;

    sf::Vector2u resolution;

    sf::RenderWindow window;
    World* world;
    std::stack<Level> levels;
    sf::Vector2f positionMainObjectInLocalView{0, 0};
    bool mainObjectInNormalXPosition = false;
    bool mainObjectInNormalYPosition = false;

    sf::View* viewWindow;

    float OXVisibleCoef = 5.0 / 14;
    float OYVisibleCoef = 513.0f / 2048;

    void input();
    void update(long long elapsedTime);
    void draw();

public:
    Engine();

    void start();

};


#endif //BOUNCE_ENGINE_H
