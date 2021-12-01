//
// Created by oop on 09.11.2021.
//

#include <iostream>
#include "../headers/Engine.h"



Engine::Engine() {
    this->resolution.x = (sf::VideoMode::getDesktopMode().width >> 2) * 3;
    this->resolution.y = (sf::VideoMode::getDesktopMode().height >> 2) * 3;

    this->window.create(sf::VideoMode(this->resolution.x, this->resolution.y), "Bounce",
                        sf::Style::Resize | sf::Style::Close);

    this->viewWindow = new sf::View(sf::FloatRect(0.f, 0.f,
                                                  static_cast<float>(this->resolution.x),
                                                  static_cast<float>(this->resolution.y)));
    //this->window.setFramerateLimit(60);
    this->window.setView(*this->viewWindow);

    this->levels.push(Level("../data/levels/level3.tmx"));
    this->levels.push(Level("../data/levels/level2.tmx"));
    this->levels.push(Level("../data/levels/level1.tmx"));

    Level level = this->levels.top();
    this->levels.pop();
    this->world = new World(level, this->resolution.x, this->resolution.y);

    sf::Vector2f startMainObjectPosition = this->world->getMainObjectPosition();
    this->positionMainObjectInLocalView.x = std::min(startMainObjectPosition.x, (float) this->resolution.x / 2);
    this->positionMainObjectInLocalView.y = std::min(startMainObjectPosition.y, (float) this->resolution.y * (1.0f - this->OYVisibleCoef));

    this->viewWindow->setCenter(std::max(startMainObjectPosition.x, (float) this->resolution.x / 2),
                                std::max(
                                        startMainObjectPosition.y - (1.0f - this->OYVisibleCoef) * (float) this->resolution.y + (float) this->resolution.y / 2,
                                        (float) this->resolution.y / 2
                                )
    );
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

        if (!this->world->isFinish()) {
            sf::Time elapsedTime = clock.restart();
            //std::cout << 1 / elapsedTime.asSeconds() << std::endl;

            input();
            update(elapsedTime.asMicroseconds());
            draw();
        } else {
            delete this->world;

            mainObjectInNormalXPosition = false;
            mainObjectInNormalYPosition = false;

            if (!this->levels.empty()) {
                this->world = new World(this->levels.top(), this->resolution.x, this->resolution.y);
                this->levels.pop();

                sf::Vector2f startMainObjectPosition = this->world->getMainObjectPosition();
                this->positionMainObjectInLocalView.x = std::min(startMainObjectPosition.x, (float) this->resolution.x / 2);
                this->positionMainObjectInLocalView.y = std::min(startMainObjectPosition.y, (float) this->resolution.y * (1.0f - this->OYVisibleCoef));

                this->viewWindow->setCenter(std::max(startMainObjectPosition.x, (float) this->resolution.x / 2),
                                            std::max(
                                                    startMainObjectPosition.y - (1.0f - this->OYVisibleCoef) * (float) this->resolution.y + (float) this->resolution.y / 2,
                                                    (float) this->resolution.y / 2
                                                    )
                                                    );
            } else {
                return;
            }
        }
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
    //float oXCoef = (float) 5 / 14;
    //float oYCoef = (float) 124 / 704;
    //float oYCoef = 1.0f / 8;

    if (this->positionMainObjectInLocalView.x >= ((float) this->window.getSize().x * this->OXVisibleCoef) && this->positionMainObjectInLocalView.x <= ((float) this->window.getSize().x * (1 - this->OXVisibleCoef))) {
        this->mainObjectInNormalXPosition = true;
    }
    if (this->positionMainObjectInLocalView.y >= ((float) this->window.getSize().y * this->OYVisibleCoef) && this->positionMainObjectInLocalView.y <= ((float) this->window.getSize().y * (1 - this->OYVisibleCoef))) {
        this->mainObjectInNormalYPosition = true;
    }

    sf::Vector2f delta = this->world->update(elapsedTime);

    float moveX = 0;
    float moveY = 0;

    if (!this->mainObjectInNormalXPosition) {
        this->positionMainObjectInLocalView.x += delta.x;
    } else {
        if (delta.x + this->positionMainObjectInLocalView.x <= ((float) this->window.getSize().x * this->OXVisibleCoef) || delta.x + this->positionMainObjectInLocalView.x >= ((float) this->window.getSize().x * (1 - this->OXVisibleCoef))) {
            moveX = delta.x;
        } else {
            this->positionMainObjectInLocalView.x += delta.x;
        }
    }

    if (!this->mainObjectInNormalYPosition) {
        this->positionMainObjectInLocalView.y += delta.y;
    } else {
        if (delta.y + this->positionMainObjectInLocalView.y <= ((float) this->window.getSize().y * this->OYVisibleCoef) || delta.y + this->positionMainObjectInLocalView.y >= ((float) this->window.getSize().y * (1 - this->OYVisibleCoef))) {
            moveY = delta.y;
        } else {
            this->positionMainObjectInLocalView.y += delta.y;
        }
    }

    this->viewWindow->move(moveX, moveY);
    //this->viewWindow->move(moveX, delta.y);
    //this->viewWindow->move(moveX, 0);
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
