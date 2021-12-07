//
// Created by oop on 30.11.2021.
//

#ifndef BOUNCE_RINGTYPE_H
#define BOUNCE_RINGTYPE_H

#include "../Surface.h"


class RingType : public Surface {

private:

    static std::unordered_map<int, std::pair<std::vector<b2Vec2>, std::vector<b2Vec2>>> globalRingPoints;
    static int numberObjectsCreated;
    int localIndex;


public:

    explicit RingType(const std::string &path);

    virtual void selectFirstHalfToDisplay();
    virtual void selectSecondHalfToDisplay();
    virtual void selectAllRingToDisplay();

    void addFirstPoint(float x, float y);
    void addFirstPoint(b2Vec2 vec);

    void addSecondPoint(float x, float y);
    void addSecondPoint(b2Vec2 vec);

    std::pair<std::vector<b2Vec2>, std::vector<b2Vec2>> getRingPoints();


    b2Fixture* buildOnEngineWithoutTop(b2World& world, float x, float y) override;
    std::pair<b2Fixture*, b2Fixture*> buildOnEngine(b2World& world, float x, float y) override;

};


#endif //BOUNCE_RINGTYPE_H
