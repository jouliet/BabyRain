#pragma once
#include "Sprite.hpp"

class Stroller : public Sprite
{
private:
    b2FixtureDef fixtureDef;
    b2Vec2      force{30, 0};

public:
    explicit    Stroller(b2World* world, float height, float width, float xPosition, float yPosition);

    void        draw(sf::RenderWindow& window) const override;
    void        update(bool movingLeft, bool movingRight) override;
};
