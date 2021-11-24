//
// Created by oop on 03.11.2021.
//

#include "../headers/World.h"
#include "../headers/surfaces/Block.h"
#include "../headers/surfaces/HalfBlock.h"
#include "../headers/surfaces/Spike.h"
#include "../headers/surfaces/Ring.h"


World::World(Level level, unsigned int width, unsigned int height) : level(level), widthWindow(width),
                                                                     heightWindow(height),
                                                                     ball(level.getImagePathByItemType(BALL)),
                                                                     //block(level.getImagePathByItemType(BRICK)),
                                                                     //half_block(level.getImagePathByItemType(HALF_BRICK)),
                                                                     //spike(level.getImagePathByItemType(SPIKE)),
                                                                     numberLives(level.getNumberLives()),
                                                                     mapItems({
                                                                         {BRICK, new Block(level.getImagePathByItemType(BRICK), sizeOfBlockInMeters)},
                                                                         {HALF_BRICK, new HalfBlock(level.getImagePathByItemType(HALF_BRICK), sizeOfBlockInMeters)},
                                                                         {SPIKE, new Spike(level.getImagePathByItemType(SPIKE), sizeOfBlockInMeters)},
                                                                         {RING, new Ring(level.getImagePathByItemType(RING), sizeOfBlockInMeters)}

                                                                     }){


    createSprites();

    this->contactListener = new ActorListener(ENEMY, [this] { touchingEnemy(); });
    this->physicalWorld.SetContactListener(this->contactListener);

    int heightLevel = level.getHeight();
    int widthLevel = level.getWidth();
    for (int i = 0; i < heightLevel; ++i) {
        for (int j = 0; j < widthLevel; ++j) {
            LevelItem item = this->level.getData()[i][j];
            if (!(item & (AIR | BALL))) {

                b2Fixture* mainFixtureOfSurface;

                if ((i == 0 || !(this->level.getData()[i - 1][j] & (BRICK | HALF_BRICK))) && this->level.getData()[i][j] & (BRICK | HALF_BRICK)) {

                    std::pair<b2Fixture*, b2Fixture*> allSurfaceFixture = this->mapItems.find(item)->second->buildOnEngine(
                            this->physicalWorld,
                            sizeOfBlockInMeters * (float) j + sizeOfBlockInMeters / 2,
                            sizeOfBlockInMeters * (float) i + sizeOfBlockInMeters / 2);

                    mainFixtureOfSurface = allSurfaceFixture.first;
                    b2Fixture* topSurface = allSurfaceFixture.second;

                    topSurface->SetRestitution(0.2f);
                    topSurface->SetFriction(100.0f);
                    topSurface->GetUserData().pointer = NO_ENEMY;
                } else {
                    if (item == RING) {
                        int h = 0 ;
                    }
                    mainFixtureOfSurface = this->mapItems.find(item)->second->buildOnEngineWithoutTop(
                            this->physicalWorld,
                            sizeOfBlockInMeters * (float) j + sizeOfBlockInMeters / 2,
                            sizeOfBlockInMeters * (float) i + sizeOfBlockInMeters / 2);
                }

                if (item & (SPIKE)) {
                    mainFixtureOfSurface->GetUserData().pointer = ENEMY;
                } else {
                    mainFixtureOfSurface->GetUserData().pointer = NO_ENEMY;
                }
                if (!(item & (RING))){
                    mainFixtureOfSurface->SetFriction(0);
                    mainFixtureOfSurface->SetRestitution(1.0f);
                }

            }
        }
    }

    this->coefForDisplay = (float) this->heightWindow / ((float) visibleHeightByBlock / (1 / sizeOfBlockInMeters));
    createBall();


}

void World::touchingEnemy() {
    this->flagBallForDelete = true;
}

void World::createBall() {

    b2Vec2 startPosition = this->level.getStartPosition();

    std::pair<b2Body*, b2Fixture*> ballComponents = this->ball.buildOnEngine(this->physicalWorld, sizeOfBlockInMeters / 2,
                             startPosition.x * sizeOfBlockInMeters - sizeOfBlockInMeters / 2,
                             startPosition.y * sizeOfBlockInMeters - sizeOfBlockInMeters / 2);
    this->ballBody = ballComponents.first;
    ballComponents.second->GetUserData().pointer = NO_ENEMY;
}


void World::createSprites() {

    for (std::pair<LevelItem const, Surface*>& surfacePair : this->mapItems) {
        sf::Vector2u size = surfacePair.second->getTexture().getSize();
        surfacePair.second->buildSprite(
                    (float) this->heightWindow / ((float) visibleHeightByBlock * (float) size.x),
                    (float) this->heightWindow / ((float) visibleHeightByBlock / (surfacePair.first == RING ? 2.0f : 1.0f) * (float) size.y));
    }

    sf::Vector2u ballSize = this->ball.getTexture().getSize();

    this->ball.buildSprite((float) this->heightWindow / ((float) visibleHeightByBlock * (float) ballSize.x),
                           (float) this->heightWindow / ((float) visibleHeightByBlock * (float) ballSize.y));
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
            if (currentSpeed.x <= -maxSpeedOX) {
                this->ballBody->SetLinearVelocity({-maxSpeedOX, currentSpeed.y});
            } else {
                this->ballBody->ApplyForceToCenter(b2Vec2(-std::pow(sizeOfBlockInMeters / 2, 3.0f) * 300000, 0),
                                                   false);
            }
            break;
        case sf::Keyboard::Right :
            if (currentSpeed.x >= maxSpeedOX) {
                this->ballBody->SetLinearVelocity({maxSpeedOX, currentSpeed.y});
            } else {
                this->ballBody->ApplyForceToCenter(b2Vec2(std::pow(sizeOfBlockInMeters / 2, 3.0f) * 300000, 0),
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
                            -std::sqrt(2 * gravityOnY * jumpSizeByBlock * sizeOfBlockInMeters)
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
                                               15.0f * sizeOfBlockInMeters});
            //this->ballBody->ApplyLinearImpulseToCenter(b2Vec2(0, 100.0f), false);
            break;

    }
}

sf::Vector2f World::update(long long elapsedTime) {

    b2Vec2 currentSpeed = this->ballBody->GetLinearVelocity();
    this->ballBody->SetLinearVelocity({currentSpeed.x * std::pow(OXDamping, (float) elapsedTime / 2000.0f), currentSpeed.y});

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
    for (int yPosition = -addedEdges; yPosition < heightLevel + addedEdges; ++yPosition) {
        for (int xPosition = -addedEdges; xPosition < widthLevel + addedEdges; ++xPosition) {
            LevelItem item;
            if (yPosition < 0 || xPosition < 0 || yPosition >= heightLevel || xPosition >= widthLevel) {
                item = BRICK;
            } else {
                item = this->level.getData()[yPosition][xPosition];
            }
            if (!(item & (BALL | AIR))) {

                sf::Sprite* sprite = this->mapItems.find(item)->second->getSprite();

                sprite->setPosition(
                        (float) xPosition * ((float) this->heightWindow / (float) visibleHeightByBlock),
                        (float) yPosition * ((float) this->heightWindow / (float) visibleHeightByBlock));

                worldWindows.draw(*sprite);
            }
        }
    }


    this->ball.getSprite()->setPosition(this->ball.getPosition());
    this->ball.getSprite()->setRotation((float) (this->ballBody->GetAngle() * 180.0 / M_PI));
    worldWindows.draw(*this->ball.getSprite());
}

