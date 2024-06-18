#pragma once
#include "Sprite.hpp"

class Stroller : public Sprite
{
private:
    b2FixtureDef fixtureDef;
    
public:
    explicit Stroller(b2World* world, float height, float width, float xPosition, float yPosition);

    void draw(sf::RenderWindow& window) const override;
    void update() override;
};
