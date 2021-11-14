//
// Created by oop on 03.11.2021.
//

#include "../headers/World.h"

World::World(Level level, unsigned int width, unsigned int height) : level(level), widthWindow(width), heightWindow(height) {

    this->worldSprite.setTexture(this->block.getTexture());
    this->ballSprite.setTexture(this->ball.getTexture());

    this->ball.setPosition(200, (float) height - 190);

}

sf::Vector2f World::getMainObjectPosition() {
    sf::Vector2u ballSize = this->ball.getTexture().getSize();
    float x = ball.getPosition().x + float (ballSize.x >> 1);
    float y = ball.getPosition().y + float (ballSize.y >> 1);
    return {x, y};
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

// add vt + at^2 / 2
sf::Vector2f World::update(long long elapsedTime) {
    //elapsedTime = 1;
    float deltaX = ((float) elapsedTime * this->powerVectorOnBall.x) / 1000;
    float deltaY = ((float) elapsedTime * this->powerVectorOnBall.y) / 2000;
    float x = this->ball.getPosition().x + deltaX;
    float y = this->ball.getPosition().y + deltaY;
    this->ball.setPosition(x, y);

    if (this->powerVectorOnBall.x >= 0) {
        this->powerVectorOnBall.x = std::max(0.0f, this->powerVectorOnBall.x - (0.000003f) * (float) elapsedTime);
    } else {
        this->powerVectorOnBall.x = std::min(0.0f, this->powerVectorOnBall.x + (0.000003f) * (float) elapsedTime);
    }
    if (this->powerVectorOnBall.y >= 0) {
        this->powerVectorOnBall.y = std::max(0.0f, this->powerVectorOnBall.y - (0.000003f) * (float) elapsedTime);
    } else {
        this->powerVectorOnBall.y = std::min(0.0f, this->powerVectorOnBall.y + (0.000003f) * (float) elapsedTime);
    }
    //std::cout << elapsedTime << std::endl;



    return {deltaX, deltaY};
}

void World::drawTexture(sf::RenderWindow& worldWindows) {

    sf::Vector2u blockSize = this->block.getTexture().getSize();

    this->worldSprite.setScale((float) this->heightWindow / (8 * (float) blockSize.x), (float) this->heightWindow / (8 * (float) blockSize.y));

    int heightLevel = this->level.getHeigth();
    int widthLevel = this->level.getWidth();
    for (int i = 0; i < heightLevel; ++i) {
        for (int j = 0; j < widthLevel; ++j) {
            if (this->level.getLevelItemById(this->level.getData()[i][j]) == BRICK) {
                this->worldSprite.setPosition((float) j * ((float) this->heightWindow / (float) heightLevel), (float) i * ((float) this->heightWindow / (float) heightLevel));

                this->worldSprite.setTextureRect(sf::IntRect(0, 0, (int) blockSize.x, (int) blockSize.y));
                worldWindows.draw(this->worldSprite);
            }
        }
    }


    sf::Vector2u ballSize = this->ball.getTexture().getSize();
    this->ballSprite.setScale((float) this->heightWindow / ((float) heightLevel * (float) ballSize.x), (float) this->heightWindow / ((float) heightLevel * (float) ballSize.y));
    this->ballSprite.setPosition(this->ball.getPosition());
    this->ballSprite.setTextureRect(sf::IntRect(0, 0, (int) blockSize.x, (int) blockSize.y));
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

