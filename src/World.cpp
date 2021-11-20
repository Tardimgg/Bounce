//
// Created by oop on 03.11.2021.
//

#include <iostream>
#include "../headers/World.h"

World::World(Level level, unsigned int width, unsigned int height) : level(level), widthWindow(width),
                                                                     heightWindow(height),
                                                                     ball(level.getImagePathByItemType(BALL)),
                                                                     //block(level.getImagePathByItemType(BRICK)),
                                                                     //half_block(level.getImagePathByItemType(HALF_BRICK)),
                                                                     //spike(level.getImagePathByItemType(SPIKE)),
                                                                     mapItems({
                                                                         {BRICK, Surface(level.getImagePathByItemType(BRICK))},
                                                                         {HALF_BRICK, Surface(level.getImagePathByItemType(HALF_BRICK))},
                                                                         {SPIKE, Surface(level.getImagePathByItemType(SPIKE))},

                                                                     }){

    this->mapItems = {
            {BRICK, Surface(level.getImagePathByItemType(BRICK))},
            {HALF_BRICK, Surface(level.getImagePathByItemType(HALF_BRICK))},
            {SPIKE, Surface(level.getImagePathByItemType(SPIKE))},

            };

    createSurface();

    this->worldSprite.setTexture(this->mapItems.find(BRICK)->second.getTexture());
    this->ballSprite.setTexture(this->ball.getTexture());


    int heightLevel = level.getHeight();
    int widthLevel = level.getWidth();
    for (int i = 0; i < heightLevel; ++i) {
        for (int j = 0; j < widthLevel; ++j) {
            LevelItem item = this->level.getData()[i][j];
            if (item & (BRICK | HALF_BRICK | SPIKE)) {
                b2BodyDef groundBodyDef;
                groundBodyDef.position.Set(this->sizeOfBlockInMeters * (float) j + this->sizeOfBlockInMeters / 2,
                                           this->sizeOfBlockInMeters * (float) i + this->sizeOfBlockInMeters / 2);
                b2Body *groundBody = this->physicalWorld.CreateBody(&groundBodyDef);

                b2PolygonShape groundBox;
                //groundBox.SetAsBox(this->sizeOfBlockInMeters / 2, this->sizeOfBlockInMeters / 2);
                std::vector<b2Vec2> points = this->mapItems.find(item)->second.getPoints();
                groundBox.Set(&points[0], (int32) points.size());

                groundBody->CreateFixture(&groundBox, 0.0f);
            }
        }
    }


    this->coef = (float) height / ((float) this->visibleHeightByBlock / (1 / this->sizeOfBlockInMeters));


    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(3.0f, 1.5);
    bodyDef.linearDamping = 5.0f;
    this->ballBody = this->physicalWorld.CreateBody(&bodyDef);

    this->dynamicBallShape.m_radius = this->sizeOfBlockInMeters / 2;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBallShape;
    fixtureDef.density = 1300.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.6f;

    this->ballBody->CreateFixture(&fixtureDef);
}

void World::createSurface() {
    float halfBlockSize = this->sizeOfBlockInMeters / 2;
    float thirdOfBlockSize = this->sizeOfBlockInMeters / 3;

    Surface block = this->mapItems.find(BRICK)->second;
    block.addPoint(-halfBlockSize, -halfBlockSize);
    block.addPoint(halfBlockSize, -halfBlockSize);
    block.addPoint(halfBlockSize, halfBlockSize);
    block.addPoint(-halfBlockSize, halfBlockSize);

    Surface half_block = this->mapItems.find(HALF_BRICK)->second;
    half_block.addPoint(-halfBlockSize, -halfBlockSize);
    half_block.addPoint(halfBlockSize, halfBlockSize);
    half_block.addPoint(-halfBlockSize, halfBlockSize);


    Surface spike = this->mapItems.find(SPIKE)->second;
    spike.addPoint(-thirdOfBlockSize, -halfBlockSize);
    spike.addPoint(thirdOfBlockSize, -halfBlockSize);
    spike.addPoint(thirdOfBlockSize, halfBlockSize);
    spike.addPoint(-thirdOfBlockSize, halfBlockSize);

}



sf::Vector2f World::getMainObjectPosition() {
    float x = this->ball.getPosition().x;
    float y = this->ball.getPosition().y;
    return {x, y};
}


void World::input(sf::Keyboard::Key addPowerVector) {
    switch (addPowerVector) {
        case sf::Keyboard::Left :
            this->ballBody->SetAwake(true);
            this->ballBody->ApplyForceToCenter(b2Vec2(-std::pow(this->sizeOfBlockInMeters, 3.0f) * 60000, 0),
                                               false);
            break;
        case sf::Keyboard::Right :
            this->ballBody->SetAwake(true);
            this->ballBody->ApplyForceToCenter(b2Vec2(std::pow(this->sizeOfBlockInMeters, 3.0f) * 60000, 0),
                                               false);
            //this->ballBody->ApplyLinearImpulseToCenter(b2Vec2(400.0f, 0), false);

            break;
        case sf::Keyboard::Up : {
            this->ballBody->SetAwake(true);

            b2ContactEdge *edge = this->ballBody->GetContactList();

            for (; edge; edge = edge->next) {
                if (edge->contact->IsTouching()) {
                    b2Vec2 normal = edge->contact->GetManifold()->localNormal;
                    if (normal.y <= -0.5) {
                        this->ballBody->SetLinearVelocity({
                            this->ballBody->GetLinearVelocity().x,
                            -std::sqrt(2 * 2.2f * this->gravityOnY * this->jumpSizeByBlock * this->sizeOfBlockInMeters)
                        });
                        //this->ballBody->ApplyLinearImpulseToCenter(b2Vec2(0, -1550.0f), false);
                        break;
                    }
                }
            }
            break;
        }
        case sf::Keyboard::Down :
            this->ballBody->SetAwake(true);
            this->ballBody->SetLinearVelocity({this->ballBody->GetLinearVelocity().x,
                                               25.0f * this->sizeOfBlockInMeters});
            //this->ballBody->ApplyLinearImpulseToCenter(b2Vec2(0, 100.0f), false);
            break;

    }
}

// add vt + at^2 / 2
sf::Vector2f World::update(long long elapsedTime) {

    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    this->physicalWorld.Step((float) elapsedTime / (float) std::pow(10, 6), velocityIterations, positionIterations);
    //this->physicalWorld.Step(1.0f / 1200, velocityIterations, positionIterations);

    b2ContactEdge *edge = this->ballBody->GetContactList();

    float deltaX = this->ballBody->GetPosition().x * this->coef - this->ball.getPosition().x;
    float deltaY = this->ballBody->GetPosition().y * this->coef - this->ball.getPosition().y;

    this->ball.setPosition(this->ballBody->GetPosition().x * this->coef,
                           this->ballBody->GetPosition().y * this->coef);

    return {deltaX, deltaY};
}


void World::drawTexture(sf::RenderWindow &worldWindows) {

    //printf("x = %f y = %f\n", this->ballBody->GetPosition().x, this->ballBody->GetPosition().y);

    sf::Vector2u blockSize = this->mapItems.find(BRICK)->second.getTexture().getSize();

    this->worldSprite.setScale((float) this->heightWindow / ((float) this->visibleHeightByBlock * (float) blockSize.x),
                               (float) this->heightWindow / ((float) this->visibleHeightByBlock * (float) blockSize.y));

    int heightLevel = this->level.getHeight();
    int widthLevel = this->level.getWidth();
    for (int yPosition = -this->addedEdges; yPosition < heightLevel + this->addedEdges; ++yPosition) {
        for (int xPosition = -this->addedEdges; xPosition < widthLevel + this->addedEdges; ++xPosition) {
            if (yPosition < 0 || xPosition < 0 || yPosition >= heightLevel || xPosition >= widthLevel ||
                this->level.getData()[yPosition][xPosition] & (BRICK | HALF_BRICK | SPIKE)) {

                this->worldSprite.setPosition(
                        (float) xPosition * ((float) this->heightWindow / (float) this->visibleHeightByBlock),
                        (float) yPosition * ((float) this->heightWindow / (float) this->visibleHeightByBlock));

                this->worldSprite.setTextureRect(sf::IntRect(0, 0, (int) blockSize.x, (int) blockSize.y));
                worldWindows.draw(this->worldSprite);
            }
        }
    }

    sf::Vector2u ballSize = this->ball.getTexture().getSize();
    this->ballSprite.setOrigin((float) ballSize.x / 2, (float) ballSize.y / 2);
    this->ballSprite.setScale((float) this->heightWindow / ((float) this->visibleHeightByBlock * (float) ballSize.x),
                              (float) this->heightWindow / ((float) this->visibleHeightByBlock * (float) ballSize.y));
    this->ballSprite.setPosition(this->ball.getPosition());
    this->ballSprite.setTextureRect(sf::IntRect(0, 0, (int) blockSize.x, (int) blockSize.y));
    worldWindows.draw(this->ballSprite);
    this->ballSprite.setRotation((float) (this->ballBody->GetAngle() * 180.0 / M_PI));

}
