//
// Created by oop on 19.11.2021.
//

#ifndef BOUNCE_SURFACE_H
#define BOUNCE_SURFACE_H


#include <unordered_map>
#include "../Environment.h"
#include "../../include/box2d/b2_math.h"
#include "../../include/box2d/b2_fixture.h"
#include "../../include/box2d/box2d.h"


class Surface : public Environment{

private:

    static std::unordered_map<int, std::vector<b2Vec2>> globalPoints;
    static std::unordered_map<int, std::vector<b2Vec2>> globalTopPoints;
    static int numberObjectsCreated;
    int localIndex;

public:

    explicit Surface(const std::string &path);

    void addPoint(float x, float y);
    void addPoint(b2Vec2 vec);

    void addTopPoint(float x, float y);
    void addTopPoint(b2Vec2 vec);

    void clearPoints();

    std::vector<b2Vec2> getPoints();
    std::vector<b2Vec2> getTopPoints();

    virtual b2Fixture* buildOnEngineWithoutTop(b2World& world, float x, float y);
    std::pair<b2Fixture*, b2Fixture*> buildOnEngine(b2World& world, float x, float y);


};


#endif //BOUNCE_SURFACE_H
