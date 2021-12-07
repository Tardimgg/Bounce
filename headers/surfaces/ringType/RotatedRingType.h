//
// Created by oop on 30.11.2021.
//

#ifndef BOUNCE_ROTATEDRINGTYPE_H
#define BOUNCE_ROTATEDRINGTYPE_H


#include "RingType.h"

class RotatedRingType : public RingType{

public:

    explicit RotatedRingType(const std::string &path);

    void selectFirstHalfToDisplay() override;
    void selectSecondHalfToDisplay() override;
    void selectAllRingToDisplay() override;

};



#endif //BOUNCE_ROTATEDRINGTYPE_H
