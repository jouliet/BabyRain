#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Sprite.hpp"
#include "Bomb.hpp"

class TripleBomb : public Bomb
{
private:
    int        type;
    float      offset{1.2f};
    float      speed{1.3f};

public:
    TripleBomb(b2World* world, float xPosition, float yPosition, float initialSpeed, int number);
    
    bool drop() override;
    void handleClick(int xPosition, int yPosition) override;
    void handleCollision(Sprite* sprite) override;
};
