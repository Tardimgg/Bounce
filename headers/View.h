//
// Created by oop on 03.11.2021.
//

#ifndef BOUNCE_VIEW_H
#define BOUNCE_VIEW_H


#include "Environment.h"

class View : public Environment {

private:
    sf::Vector2f position;

public:

    explicit View(const std::string &path);

    void setPosition(sf::Vector2f position);

    sf::Vector2f getPosition();

    void setPosition(float width, float height);
};


#endif //BOUNCE_VIEW_H
