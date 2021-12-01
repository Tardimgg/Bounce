//
// Created by oop on 30.11.2021.
//

#ifndef BOUNCE_RINGTYPE_H
#define BOUNCE_RINGTYPE_H

#include "../Surface.h"


class RingType : public Surface{

public:

    RingType(const std::string &path);

    virtual void selectFirstHalfToDisplay();
    virtual void selectSecondHalfToDisplay();
    virtual void selectAllRingToDisplay();

};




#endif //BOUNCE_RINGTYPE_H
