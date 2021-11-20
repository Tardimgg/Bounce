//
// Created by oop on 19.11.2021.
//

#ifndef BOUNCE_SURFACE_H
#define BOUNCE_SURFACE_H


#include <unordered_map>
#include "Environment.h"
#include "../include/box2d/b2_math.h"


class Surface : public Environment{

private:

    static std::unordered_map<int, std::vector<b2Vec2>> globalPoints;
    static int numberObjectsCreated;
    int localIndex;

public:

    explicit Surface(const std::string &path);

    void addPoint(float x, float y);

    std::vector<b2Vec2> getPoints();

};


#endif //BOUNCE_SURFACE_H
