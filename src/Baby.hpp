#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Sprite.hpp"
#include <random>

class Baby : public Sprite
{
private:
    b2FixtureDef fixtureDef;
    std::vector<std::unique_ptr<MyFixtureUserData>>     mFixtureUserData;

public:
    Baby(b2World* world, float height, float width);

    float       randomPosition() const;

    void        draw(sf::RenderWindow& window) const override;
    void        update(bool movingLeft, bool movingRight) override;
    void        handleCollision(Sprite* sprite) override;
    void        setDestroy() override;

};