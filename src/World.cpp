//
// Created by oop on 03.11.2021.
//

#include "../headers/World.h"

World::World() {
    this->worldSprite.setTexture(this->block.getTexture());
    this->ballSprite.setTexture(this->ball.getTexture());
    this->ball.setPosition(1, 2);

}

void World::input(sf::Keyboard::Key addPowerVector) {
    switch (addPowerVector) {
        case sf::Keyboard::Left :
            this->powerVectorOnBall.x = -1;
            break;
        case sf::Keyboard::Right :
            this->powerVectorOnBall.x = 1;
            break;
        case sf::Keyboard::Up :
            this->powerVectorOnBall.y = -1;
            break;
        case sf::Keyboard::Down :
            this->powerVectorOnBall.y = 1;
            break;

    }
}

sf::Vector2f World::update(int elapsed) {
    elapsed = 1;
    float deltaX = ((float) elapsed * this->powerVectorOnBall.x);
    float deltaY = ((float) elapsed * this->powerVectorOnBall.y);
    float x = this->ball.getPosition().x + deltaX;
    float y = this->ball.getPosition().y + deltaY;
    this->ball.setPosition(x, y);

    this->powerVectorOnBall.x = std::max(0.0f, this->powerVectorOnBall.x - 0.0003f);
    this->powerVectorOnBall.y = std::max(0.0f, this->powerVectorOnBall.y - 0.0003f);

    return {deltaX, deltaY};
}

void World::drawTexture(sf::RenderWindow& worldWindows, unsigned int width, unsigned int height) {
    int a[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    this->worldSprite.setScale((float) height / (8 * 322),(float) height / (8 * 322));
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 112; ++j) {
            if (a[i * 112 + j] == 1) {
                this->worldSprite.setPosition((float) j * ((float) height / 8),(float) i * ((float) height / 8));

                sf::Vector2u size = this->block.getTexture().getSize();
                this->worldSprite.setTextureRect(sf::IntRect(0, 0, (int) size.x, (int) size.y));
                worldWindows.draw(this->worldSprite);
            }
        }
    }

    this->ballSprite.setPosition(this->ball.getPosition());
    sf::Vector2u size = this->ball.getTexture().getSize();
    this->ballSprite.setTextureRect(sf::IntRect(0, 0, (int) size.x, (int) size.y));
    worldWindows.draw(this->ballSprite);



    //worldSprite.setScale(0.1, 0.1);
    //worldSprite.setPosition(0, 0);
    //worldSprite.setTextureRect(sf::IntRect(0, 0, 328, 322));
    //worldWindows.draw(worldSprite);
//
    //worldSprite.setScale(1, 1);
    //worldSprite.setPosition(100, 100);
    //worldSprite.setTextureRect(sf::IntRect(0, 0, 328, 322));
    //worldWindows.draw(worldSprite);
}



