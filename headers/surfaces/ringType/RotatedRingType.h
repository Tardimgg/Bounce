//
// Created by oop on 30.11.2021.
//

#ifndef BOUNCE_ROTATEDRINGTYPE_H
#define BOUNCE_ROTATEDRINGTYPE_H


#include "RingType.h"

class RotatedRingType : public RingType{

private:

    std::vector<b2Vec2> upperRing;
    std::vector<b2Vec2> lowerRing;

public:

    RotatedRingType(const std::string &path);

    void selectFirstHalfToDisplay();
    void selectSecondHalfToDisplay();
    void selectAllRingToDisplay();

};



#endif //BOUNCE_ROTATEDRINGTYPE_H
