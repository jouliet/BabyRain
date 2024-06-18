#pragma once
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

class Sprite
{
public:
    float scale = 30;
    b2BodyDef bodyDef;
    b2Body* body;
    b2PolygonShape box;
    sf::RectangleShape rec;

    virtual ~Sprite() = default;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void update() = 0;
};