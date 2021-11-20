//
// Created by oop on 09.11.2021.
//

#include <iostream>
#include "../headers/Engine.h"


Engine::Engine() {
    sf::Vector2u resolution;
    resolution.x = (sf::VideoMode::getDesktopMode().width >> 2) * 3;
    resolution.y = (sf::VideoMode::getDesktopMode().height >> 2) * 3;

    this->window.create(sf::VideoMode(resolution.x, resolution.y), "Bounce",
                        sf::Style::Resize | sf::Style::Close);

    this->viewWindow = new sf::View(sf::FloatRect(0.f, 0.f,
                                                  static_cast<float>(resolution.x),
                                                  static_cast<float>(resolution.y)));
    this->window.setView(*this->viewWindow);

    Level level("../data/levels/level1.tmx");
    this->world = new World(level, resolution.x, resolution.y);

    sf::Vector2f startMainObjectPosition = this->world->getMainObjectPosition();
    this->positionCamera.x = startMainObjectPosition.x;
    this->positionCamera.y = startMainObjectPosition.y;
}

void Engine::start() {

    sf::Clock clock;

    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                // resize my view
                viewWindow->setSize({
                    static_cast<float>(event.size.width),
                    static_cast<float>(event.size.height)
                });
                window.setView(*viewWindow);
                // and align shape

            }
        }

        sf::Time elapsedTime = clock.restart();

        input();
        update(elapsedTime.asMicroseconds());
        draw();

    }
}

void Engine::input() {
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
        this->world->input(sf::Keyboard::Left);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
        this->world->input(sf::Keyboard::Right);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) {
        this->world->input(sf::Keyboard::Up);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) {
        this->world->input(sf::Keyboard::Down);
    }
}

void Engine::update(long long elapsedTime) {
    float oXCoef = (float) 5 / 14;
    float oYCoef = (float) 124 / 704;

    if (this->positionCamera.x >= ((float) this->window.getSize().x * oXCoef) && this->positionCamera.x <= ((float) this->window.getSize().x * (1 - oXCoef))) {
        this->mainObjectInNormalXPosition = true;
    }
    if (this->positionCamera.y >= ((float) this->window.getSize().y * oYCoef) && this->positionCamera.y <= ((float) this->window.getSize().y * (1 - oYCoef))) {
        this->mainObjectInNormalYPosition = true;
    }

    sf::Vector2f delta = this->world->update(elapsedTime);

    float moveX = 0;
    float moveY = 0;

    if (!this->mainObjectInNormalXPosition) {
        this->positionCamera.x += delta.x;
    } else {
        if (delta.x + this->positionCamera.x <= ((float) this->window.getSize().x * oXCoef) || delta.x + this->positionCamera.x >= ((float) this->window.getSize().x * (1 - oXCoef))) {
            moveX = delta.x;
        } else {
            this->positionCamera.x += delta.x;
        }
    }

    if (!this->mainObjectInNormalYPosition) {
        this->positionCamera.y += delta.y;
    } else {
        if (delta.y + this->positionCamera.y <= ((float) this->window.getSize().y * oYCoef) || delta.y + this->positionCamera.y >= ((float) this->window.getSize().y * (1 - oYCoef))) {
            moveY = delta.y;
        } else {
            this->positionCamera.y += delta.y;
        }
    }

    this->viewWindow->move(moveX, moveY);
}

void Engine::draw() {

    this->window.clear(sf::Color(86, 218, 254));
    this->window.setView(*this->viewWindow);

    //sf::RenderTexture worldTexture;
    //worldTexture.create(this->resolution.x, this->resolution.y);
    //worldTexture.clear(sf::Color::Blue);
    //this->world.drawTexture(this->window, this->resolution.x, this->resolution.y);
    this->world->drawTexture(this->window);

    //sf::Sprite sprite(worldTexture.getTexture());
    //this->window.draw(sprite);
    this->window.display();
}
