#pragma once
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include "Fixtures.hpp"

class Sprite : public b2ContactListener
{
public:
    float                   scale = 30;
    b2BodyDef               bodyDef;
    b2Body*                 body;
    b2PolygonShape          box;
    sf::RectangleShape      rec;
    bool                    destroy{false};
    sf::Texture             texture;

    virtual                 ~Sprite() = default;
    virtual void            draw(sf::RenderWindow& window) const = 0;
    virtual void            update(bool movingLeft, bool movingRight) = 0;
    virtual void            handleCollision(Sprite* sprite) = 0;
    virtual void            setDestroy() = 0;
};
