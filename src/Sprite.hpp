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
    sf::Texture             texture;

    bool                    destroy{false};
    bool                    gameOver{false};

    virtual                 ~Sprite() = default;
    virtual void            draw(sf::RenderWindow& window) const = 0;
    virtual void            update(bool movingLeft, bool movingRight) = 0;
    virtual void            handleCollision(Sprite* sprite) = 0;
    virtual void            setDestroy() = 0;
    virtual void            handleClick(int xPosition, int yPosition) = 0;
    virtual void            drop() = 0;
};
