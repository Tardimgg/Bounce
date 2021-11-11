//
// Created by oop on 09.11.2021.
//

#include "../headers/Engine.h"



Engine::Engine() {
    this->resolution.x = sf::VideoMode::getDesktopMode().width >> 1;
    this->resolution.y = sf::VideoMode::getDesktopMode().height >> 1;

    this->window.create(sf::VideoMode(this->resolution.x, this->resolution.y), "Bounce", sf::Style::Resize);

    this->viewWindow = new sf::View(sf::FloatRect(0.f, 0.f, (float) this->resolution.x, (float) this->resolution.y));
    this->window.setView(*this->viewWindow);
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
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
        this->world.input(sf::Keyboard::Left);
        //--this->position.x;
        //this->viewWindow->move(-1, 0);
        //this->window.setPosition(this->position);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
        this->world.input(sf::Keyboard::Right);
        //++this->position.x;
        //this->viewWindow->move(+1, 0);
        //this->window.setPosition(this->position);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) {
        this->world.input(sf::Keyboard::Up);
        //--this->position.y;
        //this->viewWindow->move(0, -1);
        //this->window.setPosition(this->position);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) {
        this->world.input(sf::Keyboard::Down);
        //++this->position.y;
        //this->viewWindow->move(0, 1);
        //this->window.setPosition(this->position);
    }
}

void Engine::update(int elapsed) {
    this->viewWindow->move(this->world.update(elapsed));
}

void Engine::draw() {

    this->window.clear(sf::Color(86, 218, 254));
    this->window.setView(*this->viewWindow);

    //sf::RenderTexture worldTexture;
    //worldTexture.create(this->resolution.x, this->resolution.y);
    //worldTexture.clear(sf::Color::Blue);
    this->world.drawTexture(this->window, this->resolution.x, this->resolution.y);

    //sf::Sprite sprite(worldTexture.getTexture());
    //this->window.draw(sprite);
    this->window.display();
}
