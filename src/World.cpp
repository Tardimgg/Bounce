//
// Created by oop on 03.11.2021.
//

#include "../headers/World.h"


World::World(Level level, unsigned int width, unsigned int height) : level(level), widthWindow(width),
                                                                     heightWindow(height),
                                                                     ball(level.getImagePathByItemType(BALL)),
                                                                     //block(level.getImagePathByItemType(BRICK)),
                                                                     //half_block(level.getImagePathByItemType(HALF_BRICK)),
                                                                     //spike(level.getImagePathByItemType(SPIKE)),
                                                                     numberLives(level.getNumberLives()),
                                                                     mapItems({
                                                                         {BRICK, Surface(level.getImagePathByItemType(BRICK))},
                                                                         {HALF_BRICK, Surface(level.getImagePathByItemType(HALF_BRICK))},
                                                                         {SPIKE, Surface(level.getImagePathByItemType(SPIKE))},
                                                                         {RING, Surface(level.getImagePathByItemType(RING))}

                                                                     }),
                                                                     mapSprites({
                                                                         {BRICK, sf::Sprite()},
                                                                         {HALF_BRICK, sf::Sprite()},
                                                                         {SPIKE, sf::Sprite()},
                                                                         {RING, sf::Sprite()}
                                                                     }){


    createSurfaces();
    createSprites();

    this->contactListener = new ActorListener(ENEMY, [this] { touchingEnemy(); });
    this->physicalWorld.SetContactListener(this->contactListener);

    int heightLevel = level.getHeight();
    int widthLevel = level.getWidth();
    for (int i = 0; i < heightLevel; ++i) {
        for (int j = 0; j < widthLevel; ++j) {
            LevelItem item = this->level.getData()[i][j];
            if (item & (BRICK | HALF_BRICK | SPIKE)) {

                b2Fixture* mainFixtureOfSurface;

                if ((i == 0 || !(this->level.getData()[i - 1][j] & (BRICK | HALF_BRICK))) && this->level.getData()[i][j] & (BRICK | HALF_BRICK)) {

                    std::pair<b2Fixture*, b2Fixture*> allSurfaceFixture = this->mapItems.find(item)->second.buildOnEngineWithTop(this->physicalWorld,
                                                                                             this->sizeOfBlockInMeters * (float) j + this->sizeOfBlockInMeters / 2,
                                                                                             this->sizeOfBlockInMeters * (float) i + this->sizeOfBlockInMeters / 2);
                    mainFixtureOfSurface = allSurfaceFixture.first;
                    b2Fixture* topSurface = allSurfaceFixture.second;

                    topSurface->SetRestitution(0.2f);
                    topSurface->SetFriction(100.0f);
                    topSurface->GetUserData().pointer = NO_ENEMY;
                } else {
                    mainFixtureOfSurface = this->mapItems.find(item)->second.buildOnEngine(this->physicalWorld,
                                                                                           this->sizeOfBlockInMeters * (float) j + this->sizeOfBlockInMeters / 2,
                                                                                           this->sizeOfBlockInMeters * (float) i + this->sizeOfBlockInMeters / 2);
                }

                if (item & (SPIKE)) {
                    mainFixtureOfSurface->GetUserData().pointer = ENEMY;
                } else {
                    mainFixtureOfSurface->GetUserData().pointer = NO_ENEMY;
                }
                mainFixtureOfSurface->SetFriction(0);
                mainFixtureOfSurface->SetRestitution(1.0f);

            }
        }
    }

    this->coefForDisplay = (float) this->heightWindow / ((float) this->visibleHeightByBlock / (1 / this->sizeOfBlockInMeters));
    createBall();


}

void World::touchingEnemy() {
    this->flagBallForDelete = true;
}

void World::createBall() {

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    b2Vec2 startPosition = this->level.getStartPosition();
    bodyDef.position.Set(startPosition.x * this->sizeOfBlockInMeters - this->sizeOfBlockInMeters / 2,
                         startPosition.y * this->sizeOfBlockInMeters - this->sizeOfBlockInMeters / 2);
    bodyDef.angularDamping = 0.7f;
    this->ballBody = this->physicalWorld.CreateBody(&bodyDef);

    this->dynamicBallShape.m_radius = this->sizeOfBlockInMeters / 2;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBallShape;
    fixtureDef.density = 1300.0f;
    //fixtureDef.friction = 100.0f;
    //fixtureDef.restitution = 0.6f;

    b2Fixture* fixture = this->ballBody->CreateFixture(&fixtureDef);
    fixture->GetUserData().pointer = NO_ENEMY;
}

void World::createSurfaces() {
    float halfBlockSize = this->sizeOfBlockInMeters / 2;
    float sizeSpike = halfBlockSize * (126.0f / 272);

    Surface block = this->mapItems.find(BRICK)->second;
    block.addPoint(-halfBlockSize, -halfBlockSize + 0.1f);
    block.addPoint(halfBlockSize, -halfBlockSize + 0.1f);
    block.addPoint(halfBlockSize, halfBlockSize);
    block.addPoint(-halfBlockSize, halfBlockSize);
    block.addTopPoint(-halfBlockSize, -halfBlockSize);
    block.addTopPoint(halfBlockSize, -halfBlockSize);

    Surface half_block = this->mapItems.find(HALF_BRICK)->second;
    half_block.addPoint(-halfBlockSize, -halfBlockSize + 0.1f);
    half_block.addPoint(halfBlockSize, halfBlockSize + 0.1f);
    half_block.addPoint(-halfBlockSize, halfBlockSize);
    half_block.addTopPoint(-halfBlockSize, -halfBlockSize);
    half_block.addTopPoint(halfBlockSize, halfBlockSize);

    Surface spike = this->mapItems.find(SPIKE)->second;
    spike.addPoint(-sizeSpike, -halfBlockSize);
    spike.addPoint(sizeSpike, -halfBlockSize);
    spike.addPoint(sizeSpike, halfBlockSize);
    spike.addPoint(-sizeSpike, halfBlockSize);
}


void World::createSprites() {

    for (std::pair<LevelItem const, sf::Sprite>& spritePair : this->mapSprites) {
        Surface* surface = &this->mapItems.find(spritePair.first)->second;
        sf::Vector2u size = surface->getTexture().getSize();

        sf::Vector2f scaleCoef((float) this->heightWindow / ((float) this->visibleHeightByBlock * (float) size.x),
                               (float) this->heightWindow / ((float) this->visibleHeightByBlock / (spritePair.first == RING ? 2.0f : 1.0f) * (float) size.y));

        spritePair.second.setTexture(surface->getTexture());
        spritePair.second.setScale(scaleCoef);
        spritePair.second.setTextureRect(sf::IntRect(0, 0, (int) size.x, (int) size.y));
    }

    sf::Vector2u ballSize = this->ball.getTexture().getSize();

    this->ballSprite.setTexture(this->ball.getTexture());
    this->ballSprite.setOrigin((float) ballSize.x / 2, (float) ballSize.y / 2);
    this->ballSprite.setScale((float) this->heightWindow / ((float) this->visibleHeightByBlock * (float) ballSize.x),
                              (float) this->heightWindow / ((float) this->visibleHeightByBlock * (float) ballSize.y));
    this->ballSprite.setTextureRect(sf::IntRect(0, 0, (int) ballSize.x, (int) ballSize.y));
}





sf::Vector2f World::getMainObjectPosition() {
    float x = this->ball.getPosition().x;
    float y = this->ball.getPosition().y;
    return {x, y};
}


void World::input(sf::Keyboard::Key addPowerVector) {
    this->ballBody->SetAwake(true);
    b2Vec2 currentSpeed = this->ballBody->GetLinearVelocity();

    switch (addPowerVector) {
        case sf::Keyboard::Left :
            if (currentSpeed.x <= -this->maxSpeedOX) {
                this->ballBody->SetLinearVelocity({-this->maxSpeedOX, currentSpeed.y});
            } else {
                this->ballBody->ApplyForceToCenter(b2Vec2(-std::pow(this->sizeOfBlockInMeters / 2, 3.0f) * 300000, 0),
                                                   false);
            }
            break;
        case sf::Keyboard::Right :
            if (currentSpeed.x >= this->maxSpeedOX) {
                this->ballBody->SetLinearVelocity({this->maxSpeedOX, currentSpeed.y});
            } else {
                this->ballBody->ApplyForceToCenter(b2Vec2(std::pow(this->sizeOfBlockInMeters / 2, 3.0f) * 300000, 0),
                                                   false);
            }
            //this->ballBody->ApplyLinearImpulseToCenter(b2Vec2(400.0f, 0), false);

            break;
        case sf::Keyboard::Up : {

            b2ContactEdge *edge = this->ballBody->GetContactList();

            for (; edge; edge = edge->next) {
                if (edge->contact->IsTouching()) {
                    b2Vec2 normal = edge->contact->GetManifold()->localNormal;
                    if (normal.y <= -0.5) {
                        this->ballBody->SetLinearVelocity({
                            currentSpeed.x,
                            -std::sqrt(2 * this->gravityOnY * this->jumpSizeByBlock * this->sizeOfBlockInMeters)
                        });
                        //this->ballBody->ApplyLinearImpulseToCenter(b2Vec2(0, -60000.0f), false);
                        break;
                    }
                }
            }
            break;
        }
        case sf::Keyboard::Down :
            this->ballBody->SetLinearVelocity({this->ballBody->GetLinearVelocity().x,
                                               15.0f * this->sizeOfBlockInMeters});
            //this->ballBody->ApplyLinearImpulseToCenter(b2Vec2(0, 100.0f), false);
            break;

    }
}

sf::Vector2f World::update(long long elapsedTime) {

    b2Vec2 currentSpeed = this->ballBody->GetLinearVelocity();
    this->ballBody->SetLinearVelocity({currentSpeed.x * std::pow(this->OXDamping, (float) elapsedTime / 2000.0f), currentSpeed.y});

    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    this->physicalWorld.Step((float) elapsedTime / (float) std::pow(10, 6), velocityIterations, positionIterations);

    if (this->flagBallForDelete && !this->physicalWorld.IsLocked()) {
        --this->numberLives;
        if (numberLives == 0) {
            exit(0);
        }
        this->physicalWorld.DestroyBody(this->ballBody);
        this->flagBallForDelete = false;
        this->createBall();
    }
    //this->physicalWorld.ClearForces();
    //this->physicalWorld.Step(1.0f / 1200, velocityIterations, positionIterations);


    float deltaX = this->ballBody->GetPosition().x * this->coefForDisplay - this->ball.getPosition().x;
    float deltaY = this->ballBody->GetPosition().y * this->coefForDisplay - this->ball.getPosition().y;

    this->ball.setPosition(this->ballBody->GetPosition().x * this->coefForDisplay,
                           this->ballBody->GetPosition().y * this->coefForDisplay);

    return {deltaX, deltaY};
}


void World::drawTexture(sf::RenderWindow &worldWindows) {

    //printf("x = %f y = %f\n", this->ballBody->GetPosition().x, this->ballBody->GetPosition().y);



    int heightLevel = this->level.getHeight();
    int widthLevel = this->level.getWidth();
    for (int yPosition = -this->addedEdges; yPosition < heightLevel + this->addedEdges; ++yPosition) {
        for (int xPosition = -this->addedEdges; xPosition < widthLevel + this->addedEdges; ++xPosition) {
            LevelItem item;
            if (yPosition < 0 || xPosition < 0 || yPosition >= heightLevel || xPosition >= widthLevel) {
                item = BRICK;
            } else {
                item = this->level.getData()[yPosition][xPosition];
            }
            if (!(item & (BALL | AIR))) {

                sf::Sprite* sprite = &this->mapSprites.find(item)->second;

                sprite->setPosition(
                        (float) xPosition * ((float) this->heightWindow / (float) this->visibleHeightByBlock),
                        (float) yPosition * ((float) this->heightWindow / (float) this->visibleHeightByBlock));

                worldWindows.draw(*sprite);
            }
        }
    }


    this->ballSprite.setPosition(this->ball.getPosition());
    this->ballSprite.setRotation((float) (this->ballBody->GetAngle() * 180.0 / M_PI));
    worldWindows.draw(this->ballSprite);
}

