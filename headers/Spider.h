//
// Created by oop on 30.11.2021.
//

#ifndef BOUNCE_SPIDER_H
#define BOUNCE_SPIDER_H

#include "FlyingView.h"
#include "../headers/Level.h"


class Spider {

private:

    b2Vec2 movement;
    b2Vec2 startPosition;
    b2Vec2 stopPosition;
    std::vector<b2Vec2> points;
    bool moveToEnd = true;

    static FlyingView* view;

public:

    Spider(b2Vec2 startPosition, b2Vec2 stopPosition, b2Vec2 moving, float side);

    std::pair<b2Body *, b2Fixture *> buildOnEngine(b2World& world);
    std::pair<b2Body *, b2Fixture *> buildOnEngine(b2World& world, float x, float y);

    b2Vec2 getMoving();

    void setPosition(b2Vec2);

    static FlyingView* getView();

    static void initView(const std::string& path);


};




#endif //BOUNCE_SPIDER_H
