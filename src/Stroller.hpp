#pragma once
#include "Sprite.hpp"
#include <SFML/Audio.hpp>

class Stroller : public Sprite
{
private:
    b2FixtureDef       fixtureDef;
    b2Vec2             force{30, 0};
    std::vector<std::unique_ptr<MyFixtureUserData>>     mFixtureUserData;

public:
    explicit    Stroller(b2World* world, float height, float width, float xPosition, float yPosition);

    void        draw(sf::RenderWindow& window) const override;
    void        update(bool movingLeft, bool movingRight) override;
    void        handleCollision(Sprite* sprite) override;
    void        setDestroy() override;

};
