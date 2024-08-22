#pragma once
#include "Sprite.hpp"

class StaticSprite : public Sprite
{
public:
    explicit StaticSprite(b2World* world, float height, float width, float xPosition, float yPosition);

    void            draw(sf::RenderWindow& window) const override;
    void            update(bool movingLeft, bool movingRight) override;
    void            handleCollision(Sprite* sprite) override;
    void            setDestroy() override;
    void            handleClick(int xPosition, int yPosition) override {/* does nothing */};
    void            drop() override {/*does nothing*/};
};
