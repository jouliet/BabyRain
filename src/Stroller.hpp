#pragma once
#include "Sprite.hpp"
#include <SFML/Audio.hpp>

class Stroller : public Sprite
{
private:
    b2Vec2          force{30, 0};

public:
    explicit        Stroller(b2WorldId worldId, float height, float width, float xPosition, float yPosition);

    void            draw(sf::RenderWindow& window) const override;
    void            update(bool movingLeft, bool movingRight) override;
    void            handleCollision(Sprite* sprite) override;
    void            setDestroy() override;

};
