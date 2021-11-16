//
// Created by oop on 03.11.2021.
//

#include <iostream>
#include "../headers/World.h"

World::World(Level level, unsigned int width, unsigned int height) :  level(level), widthWindow(width), heightWindow(height),
                                                                            ball(level.getImagePathByItemType(BALL)),
                                                                            block(level.getImagePathByItemType(BRICK)) {

    this->worldSprite.setTexture(this->block.getTexture());
    this->ballSprite.setTexture(this->ball.getTexture());

    this->ball.setPosition(200, (float) height - 700);


    float coef = 1;

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f,1.15f);
    b2Body* groundBody = this->physicalWorld.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(5000.0f, 0.1f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.1f, 0.1);
    bodyDef.linearDamping = 5.0f;
    this->ballBody = this->physicalWorld.CreateBody(&bodyDef);

    this->dynamicBallShape.m_radius = 0.2f;
    //b2PolygonShape dynamicBallShape;
    //dynamicBallShape.SetAsBox(1, 1);



    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBallShape;
    fixtureDef.density = 1300.0f;
    fixtureDef.friction = 0.3f;

    this->ballBody->CreateFixture(&fixtureDef);


}

sf::Vector2f World::getMainObjectPosition() {
    sf::Vector2u ballSize = this->ball.getTexture().getSize();
    float x = ball.getPosition().x;
    float y = ball.getPosition().y;
    return {x, y};
}


void World::input(sf::Keyboard::Key addPowerVector) {
    this->ballBody->SetAwake(true);

    switch (addPowerVector) {
        case sf::Keyboard::Left :
            this->ballBody->ApplyForceToCenter(b2Vec2(-2000.0f, 0), false);
            //this->powerVectorOnBall.x = -1;
            break;
        case sf::Keyboard::Right :
            this->ballBody->ApplyForceToCenter(b2Vec2(2000.0f, 0), false);
            //this->ballBody->ApplyLinearImpulseToCenter(b2Vec2(400.0f, 0), false);

            //this->powerVectorOnBall.x = 1;
            break;
        case sf::Keyboard::Up : {


                b2ContactEdge* edge = this->ballBody->GetContactList();

                if (edge != nullptr && edge->contact->IsTouching()) {

                    b2Vec2 normal = edge->contact->GetManifold()->localNormal;
                    if (normal.y != 0) {
                        this->ballBody->SetLinearVelocity({this->ballBody->GetLinearVelocity().x, -6.5});
                        //this->ballBody->ApplyLinearImpulseToCenter(b2Vec2(0, -550.0f), false);
                    }
                }
                //this->ballBody->Ga
                //this->powerVectorOnBall.y = -1;
                break;
            }
        case sf::Keyboard::Down :
            this->ballBody->SetLinearVelocity({this->ballBody->GetLinearVelocity().x, 3});
            //this->ballBody->ApplyLinearImpulseToCenter(b2Vec2(0, 100.0f), false);
            //this->powerVectorOnBall.y = 1;
            break;

    }
}

// add vt + at^2 / 2
sf::Vector2f World::update(long long elapsedTime) {

    b2ContactEdge* edge = this->ballBody->GetContactList();


    //if (edge != nullptr) {
    //    bool notTouchesOX = false;
    //    if (edge->contact->IsTouching()) {
    //        b2Vec2 normal = edge->contact->GetManifold()->localNormal;
    //        if (normal.y == 0) {
    //            notTouchesOX = true;
    //        }
    //    }
//
    //    if (this->ballIsReadyJump && (!edge->contact->IsTouching() || notTouchesOX)) {
    //        this->ballIsFly = true;
    //        this->ballIsReadyJump = false;
    //        std::cout << "coci" << std::endl;
    //    } else if (!notTouchesOX && edge->contact->IsTouching()){
    //        this->ballIsFly = false;
    //    }
    //} else {
    //    this->ballIsReadyJump = false;
    //    this->ballIsFly = true;
    //}



    int32 velocityIterations = 8;
    int32 positionIterations = 3;



    this->physicalWorld.Step((float) elapsedTime / 1000000, velocityIterations, positionIterations);
    //this->physicalWorld.Step(1.0f / 1200, velocityIterations, positionIterations);


    float deltaX = this->ballBody->GetPosition().x * 750 - this->ball.getPosition().x;
    float deltaY = this->ballBody->GetPosition().y * 750 - this->ball.getPosition().y;

    this->ball.setPosition(this->ballBody->GetPosition().x * 750, this->ballBody->GetPosition().y * 750);






    //elapsedTime = 1;
    //float deltaX = ((float) elapsedTime * this->powerVectorOnBall.x) / 1000;
    //float deltaY = ((float) elapsedTime * this->powerVectorOnBall.y) / 2000;
    //float x = this->ball.getPosition().x + deltaX;
    //float y = this->ball.getPosition().y + deltaY;
    //this->ball.setPosition(x, y);
//
    //if (this->powerVectorOnBall.x >= 0) {
    //    this->powerVectorOnBall.x = std::max(0.0f, this->powerVectorOnBall.x - (0.000003f) * (float) elapsedTime);
    //} else {
    //    this->powerVectorOnBall.x = std::min(0.0f, this->powerVectorOnBall.x + (0.000003f) * (float) elapsedTime);
    //}
    //if (this->powerVectorOnBall.y >= 0) {
    //    this->powerVectorOnBall.y = std::max(0.0f, this->powerVectorOnBall.y - (0.000003f) * (float) elapsedTime);
    //} else {
    //    this->powerVectorOnBall.y = std::min(0.0f, this->powerVectorOnBall.y + (0.000003f) * (float) elapsedTime);
    //}
    ////std::cout << elapsedTime << std::endl;



    return {deltaX, deltaY};
}

void World::drawTexture(sf::RenderWindow& worldWindows) {



    for (int32 i = 0; i < 1; ++i)
    {
        //this->physicalWorld.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = ballBody->GetPosition();
        float angle = ballBody->GetAngle();
        //printf("%4.2f %4.2f %4.2f %d\n", position.x, position.y, angle, ballBody->IsAwake());
    }


    sf::Vector2u blockSize = this->block.getTexture().getSize();

    this->worldSprite.setScale((float) this->heightWindow / ((float) this->level.getHeigth() * (float) blockSize.x), (float) this->heightWindow / ((float) this->level.getHeigth() * (float) blockSize.y));

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
    this->ballSprite.setOrigin((float) ballSize.x / 2, (float) ballSize.y / 2);
    this->ballSprite.setScale((float) this->heightWindow / ((float) heightLevel * (float) ballSize.x), (float) this->heightWindow / ((float) heightLevel * (float) ballSize.y));
    this->ballSprite.setPosition(this->ball.getPosition());
    this->ballSprite.setTextureRect(sf::IntRect(0, 0, (int) blockSize.x, (int) blockSize.y));
    worldWindows.draw(this->ballSprite);
    this->ballSprite.setRotation(this->ballBody->GetAngle() * 100);



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

