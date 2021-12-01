//
// Created by oop on 03.11.2021.
//

#include "../headers/World.h"
#include "../headers/surfaces/blockType/Block.h"
#include "../headers/surfaces/blockType/LeftHalfBlock.h"
#include "../headers/surfaces/Spike.h"
#include "../headers/surfaces/ringType/Ring.h"
#include "../headers/surfaces/ringType/RotatedRing.h"
#include "../headers/surfaces/EndLevel.h"
#include "../headers/surfaces/blockType/RightHalfBlock.h"
#include "../headers/surfaces/Diminutive.h"
#include "../headers/surfaces/Magnifier.h"
#include "../headers/surfaces/ringType/BigRing.h"
#include "../headers/surfaces/ringType/RotatedBigRing.h"
#include "../headers/Spider.h"
#include "../headers/surfaces/JumpBlock.h"
#include "../headers/surfaces/blockType/TopLeftHalfBlock.h"
#include "../headers/surfaces/blockType/TopRightHalfBlock.h"


World::World(Level level, unsigned int width, unsigned int height) :
                          level(level), widthWindow(width),
                          heightWindow(height),
                          ball(level.getImagePathByItemType(BALL)),
                          numberLives(level.getNumberLives()),
                          numberUnvisitedRings(level.getNumberRings()),
                          mapItems({
                              {BRICK,                   new Block(level.getImagePathByItemType(BRICK), sizeOfBlockInMeters)},
                              {LEFT_HALF_BRICK,         new LeftHalfBlock(level.getImagePathByItemType(LEFT_HALF_BRICK), sizeOfBlockInMeters)},
                              {RIGHT_HALF_BRICK,        new RightHalfBlock(level.getImagePathByItemType(RIGHT_HALF_BRICK), sizeOfBlockInMeters)},
                              {SPIKE,                   new Spike(level.getImagePathByItemType(SPIKE), sizeOfBlockInMeters)},
                              {RING,                    new Ring(level.getImagePathByItemType(RING), sizeOfBlockInMeters)},
                              {VISITED_RING,            new Ring(level.getImagePathByItemType(VISITED_RING), sizeOfBlockInMeters)},
                              {ROTATED_RING,            new RotatedRing(level.getImagePathByItemType(ROTATED_RING), sizeOfBlockInMeters)},
                              {VISITED_ROTATED_RING,    new RotatedRing(level.getImagePathByItemType(VISITED_ROTATED_RING), sizeOfBlockInMeters)},
                              {BIG_RING,                new BigRing(level.getImagePathByItemType(BIG_RING), sizeOfBlockInMeters)},
                              {VISITED_BIG_RING,        new BigRing(level.getImagePathByItemType(VISITED_BIG_RING), sizeOfBlockInMeters)},
                              {ROTATED_BIG_RING,        new RotatedBigRing(level.getImagePathByItemType(ROTATED_BIG_RING), sizeOfBlockInMeters)},
                              {VISITED_ROTATED_BIG_RING,new RotatedBigRing(level.getImagePathByItemType(VISITED_ROTATED_BIG_RING), sizeOfBlockInMeters)},
                              {CLOSE_END_LEVEL,         new EndLevel(level.getImagePathByItemType(CLOSE_END_LEVEL), sizeOfBlockInMeters)},
                              {END_LEVEL,               new EndLevel(level.getImagePathByItemType(END_LEVEL), sizeOfBlockInMeters)},
                              {TO_LOWER_ITEM,           new Diminutive(level.getImagePathByItemType(TO_LOWER_ITEM), sizeOfBlockInMeters)},
                              {TO_UPPER_ITEM,           new Magnifier(level.getImagePathByItemType(TO_UPPER_ITEM), sizeOfBlockInMeters)},
                              {JUMP_BRICK,              new JumpBlock(level.getImagePathByItemType(JUMP_BRICK), sizeOfBlockInMeters)},
                              {TOP_LEFT_HALF_BLOCK,     new TopLeftHalfBlock(level.getImagePathByItemType(TOP_LEFT_HALF_BLOCK), sizeOfBlockInMeters)},
                              {TOP_RIGHT_HALF_BLOCK,    new TopRightHalfBlock(level.getImagePathByItemType(TOP_RIGHT_HALF_BLOCK), sizeOfBlockInMeters)}
                          }){


    Spider::initView(level.getImagePathByItemType(OX_SPIDER));
    createSprites();

    this->contactListener = new ActorListener([this] { touchingEnemy(); },
                                              [this] { touchingToLower(); },
                                              [this] { touchingToUpper(); },
                                              std::bind(&World::touchingBonus, this, std::placeholders::_1),
                                              [this] { finishLevel(); });
    this->physicalWorld.SetContactListener(this->contactListener);

    int heightLevel = level.getHeight();
    int widthLevel = level.getWidth();
    for (int i = 0; i < heightLevel; ++i) {
        for (int j = 0; j < widthLevel; ++j) {
            LevelItem item = this->level.getData()[i][j];
            if (!(item & (AIR | BALL | OX_SPIDER | OY_SPIDER))) {

                if (i == 0 || !(this->level.getData()[i - 1][j] & (BRICK | LEFT_HALF_BRICK | RIGHT_HALF_BRICK |
                    JUMP_BRICK | TOP_LEFT_HALF_BLOCK | TOP_RIGHT_HALF_BLOCK)) ||
                    this->level.getData()[i][j] & (RING | BIG_RING)) {

                    std::pair<b2Fixture*, b2Fixture*> fixturePair = this->mapItems.find(item)->second->buildOnEngine(
                            this->physicalWorld,
                            sizeOfBlockInMeters * (float) j + sizeOfBlockInMeters / 2,
                            sizeOfBlockInMeters * (float) i + sizeOfBlockInMeters / 2);

                    if (item & (RING | ROTATED_RING | BIG_RING | ROTATED_BIG_RING)) {
                        fixturePair.first->GetBody()->GetUserData().pointer = reinterpret_cast<uintptr_t>(
                                new sf::Vector2i(i, j)
                        );
                    }

                } else {
                    this->mapItems.find(item)->second->buildOnEngineWithoutTop(
                            this->physicalWorld,
                            sizeOfBlockInMeters * (float) j + sizeOfBlockInMeters / 2,
                            sizeOfBlockInMeters * (float) i + sizeOfBlockInMeters / 2);
                }
            }
            else if (item & (OX_SPIDER | OY_SPIDER)) {
                sf::Vector2i findIndex;
                b2Vec2 movement;
                sf::Vector2i step;


                if (item & OX_SPIDER) {
                    if (this->level.getData()[i][j + 2] == AIR) {
                        step = sf::Vector2i(1, 0);
                        movement = b2Vec2(1, 0);
                    } else {
                        step = sf::Vector2i(-1, 0);
                        movement = b2Vec2(-1, 0);
                    }
                    findIndex = findBorder(BRICK | LEFT_HALF_BRICK | RIGHT_HALF_BRICK | JUMP_BRICK |
                                                            TOP_LEFT_HALF_BLOCK | TOP_RIGHT_HALF_BLOCK, {j, i},
                                                        {step.x > 0 ? widthLevel : 0, i}, step);
                    findIndex.x += step.x > 0 ? -2 : 1;
                } else {
                    if (this->level.getData()[i + 2][j] == AIR) {
                        step = sf::Vector2i(0, 1);
                        movement = b2Vec2(0, 1);
                    } else {
                        step = sf::Vector2i(0, -1);
                        movement = b2Vec2(0, -1);
                    }
                    findIndex = findBorder(BRICK | LEFT_HALF_BRICK | RIGHT_HALF_BRICK |
                                            JUMP_BRICK | TOP_LEFT_HALF_BLOCK | TOP_RIGHT_HALF_BLOCK,
                                            {j, i},
                                           {j, step.y > 0 ? heightLevel : 0}, step);
                    findIndex.y += step.y > 0 ? -2 : 1;

                }
                Spider spider(
                        {
                            (float) j * sizeOfBlockInMeters + sizeOfBlockInMeters,
                            (float) i * sizeOfBlockInMeters + sizeOfBlockInMeters
                            },
                            {
                            (float) findIndex.x * sizeOfBlockInMeters + sizeOfBlockInMeters,
                            (float) findIndex.y * sizeOfBlockInMeters + sizeOfBlockInMeters
                            },
                            movement,
                            sizeOfBlockInMeters
                            );
                b2Body* spiderBody = spider.buildOnEngine(
                        this->physicalWorld,
                        sizeOfBlockInMeters * (float) j + sizeOfBlockInMeters,
                        sizeOfBlockInMeters * (float) i + sizeOfBlockInMeters
                        ).first;
                this->spiders.emplace_back(spider, spiderBody);

            }
        }
    }

    this->coefForDisplay = (float) this->heightWindow / ((float) visibleHeightByBlock / (1 / sizeOfBlockInMeters));
    createBall();
    this->ball.setPosition(this->ballBody->GetPosition().x * this->coefForDisplay,
                           this->ballBody->GetPosition().y * this->coefForDisplay);

}

sf::Vector2i World::findBorder(unsigned int border, sf::Vector2i start, sf::Vector2i end, sf::Vector2i step) {
    while (start.x != end.x || start.y != end.y) {
        LevelItem w = this->level.getData()[start.y][start.x];
        if (this->level.getData()[start.y][start.x] & border) {
            return start;
        }
        start += step;
    }
    return {-1, -1};
}

void World::touchingEnemy() {
    this->flagBallForDelete = true;
}

void World::touchingToLower() {
    this->flagBallToLower = true;
}

void World::touchingToUpper() {
    this->flagBallToUpper = true;
}

void World::touchingBonus(sf::Vector2i coord) {
    if (this->level.getData()[coord.x][coord.y] & (RING | ROTATED_RING)) {
        this->level.getData()[coord.x][coord.y] = this->level.getData()[coord.x][coord.y] & RING ?
                VISITED_RING : VISITED_ROTATED_RING;
        --this->numberUnvisitedRings;
    }
    if (this->level.getData()[coord.x][coord.y] & (BIG_RING | ROTATED_BIG_RING)) {
        this->level.getData()[coord.x][coord.y] = this->level.getData()[coord.x][coord.y] & BIG_RING ?
                VISITED_BIG_RING : VISITED_ROTATED_BIG_RING;
        --this->numberUnvisitedRings;
    }
}

void World::finishLevel() {
    if (this->numberUnvisitedRings == 0) {
        this->finish = true;
    }
}

bool World::isFinish() {
    return this->finish;
}

void World::createBall(float radius) {

    b2Vec2 startPosition = this->level.getStartPosition();

    std::pair<b2Body*, b2Fixture*> ballComponents = this->ball.buildOnEngine(this->physicalWorld, radius,
                             startPosition.x * sizeOfBlockInMeters - sizeOfBlockInMeters / 2,
                             startPosition.y * sizeOfBlockInMeters - sizeOfBlockInMeters / 2);
    this->ballBody = ballComponents.first;
}

void World::createBall(b2Vec2 position, float radius) {

    std::pair<b2Body*, b2Fixture*> ballComponents = this->ball.buildOnEngine(this->physicalWorld, radius,
                                                                             position.x, position.y);
    this->ballBody = ballComponents.first;
}

void World::createSprites() {

    for (std::pair<LevelItem const, Surface*>& surfacePair : this->mapItems) {
        sf::Vector2u size = surfacePair.second->getTexture().getSize();

        int OY2Type = RING | VISITED_RING | BIG_RING | VISITED_BIG_RING | END_LEVEL | CLOSE_END_LEVEL;
        int OX2Type = ROTATED_RING | VISITED_ROTATED_RING | ROTATED_BIG_RING | VISITED_ROTATED_BIG_RING | END_LEVEL | CLOSE_END_LEVEL;

        int END_LEVEL_TYPE = END_LEVEL | CLOSE_END_LEVEL;
        surfacePair.second->buildSprite(
                ((float) this->heightWindow / ((float) visibleHeightByBlock / (surfacePair.first & OX2Type ? 2.0f : 1.0f) * (float) size.x)) *
                    (surfacePair.first & END_LEVEL_TYPE ? 1.0f : 1.01f),
                ((float) this->heightWindow / ((float) visibleHeightByBlock / (surfacePair.first & OY2Type ? 2.0f : 1.0f) * (float) size.y)) *
                    (surfacePair.first & END_LEVEL_TYPE ? 1.0f : 1.01f));
    }

    sf::Vector2u ballSize = this->ball.getTexture().getSize();

    this->ball.buildSprite((float) this->heightWindow / ((float) visibleHeightByBlock * (float) ballSize.x),
                           (float) this->heightWindow / ((float) visibleHeightByBlock * (float) ballSize.y));

    sf::Vector2u spikeSize = Spider::getView()->getTexture().getSize();

    Spider::getView()->buildSprite(
            ((float) this->heightWindow / ((float) visibleHeightByBlock / 2 * (float) spikeSize.x)),
            ((float) this->heightWindow / ((float) visibleHeightByBlock / 2 * (float) spikeSize.y))
    );
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
                this->ballBody->ApplyForceToCenter(b2Vec2(-std::pow(sizeOfBlockInMeters / 2, 3.0f)
                                                                        * 600000 * (this->ballIsSmall ? 1 : 1.4f), 0),
                                                                    false);
            }
            break;
        case sf::Keyboard::Right :
            if (currentSpeed.x >= maxSpeedOX) {
                this->ballBody->SetLinearVelocity({maxSpeedOX, currentSpeed.y});
            } else {
                this->ballBody->ApplyForceToCenter(b2Vec2(std::pow(sizeOfBlockInMeters / 2, 3.0f)
                                                                        * 600000 * (this->ballIsSmall ? 1 : 1.4f), 0),
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
                            -std::sqrt(2 * gravityOnY * jumpSizeByBlock * sizeOfBlockInMeters * (this->ballIsSmall ? 1 : 1.4f))
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

    for (std::pair<Spider, b2Body*>& spider : this->spiders) {
        spider.first.setPosition(spider.second->GetPosition());
        b2Vec2 movingSpider = spider.first.getMoving();
        spider.second->SetLinearVelocity({
            sizeOfBlockInMeters * 1.5f * movingSpider.x,
            sizeOfBlockInMeters * 1.5f * movingSpider.y
        });
    }

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

        if (!this->ballIsSmall) {
            this->ball.getSprite()->scale(1.0f / 1.3f, 1.0f / 1.3f);
            this->ballIsSmall = true;
        }
    }

    if ((this->flagBallToLower && !this->ballIsSmall || this->flagBallToUpper && this->ballIsSmall)
        && !this->physicalWorld.IsLocked()) {

        this->physicalWorld.DestroyBody(this->ballBody);

        this->createBall(this->ballBody->GetPosition(),
                         this->flagBallToLower ?
                         sizeOfBlockInMeters / 2.0f - sizeOfBlockInMeters / 100.0f :
                         sizeOfBlockInMeters / 2.0f * 1.3f);
        if (this->ballIsSmall) {
            this->ball.getSprite()->scale(1.3f, 1.3f);
        } else {
            this->ball.getSprite()->scale(1.0f / 1.3f, 1.0f / 1.3f);
        }

        this->ballIsSmall = flagBallToLower;

    }
    this->flagBallToLower = false;
    this->flagBallToUpper = false;

    float deltaX = this->ballBody->GetPosition().x * this->coefForDisplay - this->ball.getPosition().x;
    float deltaY = this->ballBody->GetPosition().y * this->coefForDisplay - this->ball.getPosition().y;

    this->ball.setPosition(this->ballBody->GetPosition().x * this->coefForDisplay,
                           this->ballBody->GetPosition().y * this->coefForDisplay);

    return {deltaX, deltaY};
}


void World::drawTexture(sf::RenderWindow &worldWindows) {

    int heightLevel = this->level.getHeight();
    int widthLevel = this->level.getWidth();

    ((RingType*) this->mapItems.find(RING)->second)->selectSecondHalfToDisplay();
    ((RingType*) this->mapItems.find(VISITED_RING)->second)->selectSecondHalfToDisplay();
    ((RotatedRingType*) this->mapItems.find(ROTATED_RING)->second)->selectFirstHalfToDisplay();
    ((RotatedRingType*) this->mapItems.find(VISITED_ROTATED_RING)->second)->selectFirstHalfToDisplay();
    ((RingType*) this->mapItems.find(BIG_RING)->second)->selectSecondHalfToDisplay();
    ((RingType*) this->mapItems.find(VISITED_BIG_RING)->second)->selectSecondHalfToDisplay();
    ((RotatedRingType*) this->mapItems.find(ROTATED_BIG_RING)->second)->selectFirstHalfToDisplay();
    ((RotatedRingType*) this->mapItems.find(VISITED_ROTATED_BIG_RING)->second)->selectFirstHalfToDisplay();

    for (int yPosition = -addedEdges; yPosition < heightLevel + addedEdges; ++yPosition) {
        for (int xPosition = -addedEdges; xPosition < widthLevel + addedEdges; ++xPosition) {
            LevelItem item;
            if (yPosition < 0 || xPosition < 0 || yPosition >= heightLevel || xPosition >= widthLevel) {
                item = BRICK;
            } else {
                item = this->level.getData()[yPosition][xPosition];
            }
            if (item == CLOSE_END_LEVEL && this->numberUnvisitedRings == 0) {
                item = END_LEVEL;
                this->level.getData()[yPosition][xPosition] = item;
            }

            if (!(item & (BALL | AIR | OX_SPIDER | OY_SPIDER))) {

                if (item & (RING | VISITED_RING | ROTATED_RING | VISITED_ROTATED_RING |
                    BIG_RING | VISITED_BIG_RING | ROTATED_BIG_RING | VISITED_ROTATED_BIG_RING)) {

                    if (this->arrangementOfRing.size() != this->level.getNumberRings()) {
                        this->arrangementOfRing.emplace_back(yPosition, xPosition);
                    }
                }
                sf::Sprite* sprite = this->mapItems.find(item)->second->getSprite();

                sprite->setPosition(
                        ((float) xPosition + (item & (RING | VISITED_RING | BIG_RING | VISITED_BIG_RING)
                            ? 0.49f : 0)) * ((float) this->heightWindow / (float) visibleHeightByBlock),
                        (float) yPosition * ((float) this->heightWindow / (float) visibleHeightByBlock));

                worldWindows.draw(*sprite);
            }
        }
    }

    for (std::pair<Spider, b2Body*> spider : this->spiders) {
        Spider::getView()->getSprite()->setPosition(spider.second->GetPosition().x * this->coefForDisplay,
                                                    spider.second->GetPosition().y * this->coefForDisplay);
        worldWindows.draw(*Spider::getView()->getSprite());

    }

    this->ball.getSprite()->setPosition(this->ball.getPosition());
    this->ball.getSprite()->setRotation((float) (this->ballBody->GetAngle() * 180.0 / M_PI));
    worldWindows.draw(*this->ball.getSprite());


    ((RingType*) this->mapItems.find(RING)->second)->selectFirstHalfToDisplay();
    ((RingType*) this->mapItems.find(VISITED_RING)->second)->selectFirstHalfToDisplay();
    ((RotatedRingType*) this->mapItems.find(ROTATED_RING)->second)->selectSecondHalfToDisplay();
    ((RotatedRingType*) this->mapItems.find(VISITED_ROTATED_RING)->second)->selectSecondHalfToDisplay();
    ((RingType*) this->mapItems.find(BIG_RING)->second)->selectFirstHalfToDisplay();
    ((RingType*) this->mapItems.find(VISITED_BIG_RING)->second)->selectFirstHalfToDisplay();
    ((RotatedRingType*) this->mapItems.find(ROTATED_BIG_RING)->second)->selectSecondHalfToDisplay();
    ((RotatedRingType*) this->mapItems.find(VISITED_ROTATED_BIG_RING)->second)->selectSecondHalfToDisplay();

    for (std::pair<int, int>& value : this->arrangementOfRing) {
        LevelItem item = this->level.getData()[value.first][value.second];
        sf::Sprite* sprite = this->mapItems.find(item)->second->getSprite();
        sprite->setPosition((float) value.second * ((float) this->heightWindow / (float) visibleHeightByBlock),
                            ((float) value.first + (item & (ROTATED_RING | VISITED_ROTATED_RING |
                                ROTATED_BIG_RING | VISITED_ROTATED_BIG_RING) ? 0.49f : 0)) *
                            ((float) this->heightWindow / (float) visibleHeightByBlock));

        worldWindows.draw(*sprite);
    }
}