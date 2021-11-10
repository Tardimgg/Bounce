//
// Created by oop on 09.11.2021.
//

#include "../headers/Engine.h"



Engine::Engine() {
    sf::Vector2u resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;

    this->window.create(sf::VideoMode(resolution.x >> 1, resolution.y >> 1), "Bounce", sf::Style::Resize);

}

void Engine::start() {

    sf::Clock clock;

    while (window.isOpen()) {

        sf::Time elapsed = clock.restart();

        input();
        update(elapsed.asMilliseconds());
        draw();

    }
}

void Engine::input() {

}

void Engine::update(int elapsed) {

}

void Engine::draw() {

    this->window.clear(sf::Color::White);

    this->window.display();

}
