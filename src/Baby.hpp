#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Sprite.hpp"
#include <random>

class Game;

class Baby : public Sprite
{
private:
    float       halfHeight{1.0f};
    float       halfWidth{0.5f};
    float       speed{-1.2f};

    b2FixtureDef                           fixtureDef;
    std::unique_ptr<MyFixtureUserData>     fixtureUserData;

public:
    Baby(b2World* world, float xPosition, float yPosition, float initialSpeed);

    void        draw(sf::RenderWindow& window) const override;
    void        update(bool movingLeft, bool movingRight) override;
    void        handleCollision(Sprite* sprite) override;
    void        setDestroy() override;
    void        handleClick(int xPosition, int yPosition) override {/* does nothing */};
    bool        drop() override;
};
