#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Sprite.hpp"
#include <random>

class Bomb : public Sprite
{
private:
    float       halfHeight{1};
    float       halfWidth{1};
    float       speed{-2};

    b2FixtureDef                           fixtureDef;
    std::unique_ptr<MyFixtureUserData>     fixtureUserData;
    
public:
    Bomb(b2World* world, float xPosition, float yPosition, float initialSpeed);

    void        draw(sf::RenderWindow& window) const override;
    void        update(bool movingLeft, bool movingRight) override;
    void        handleCollision(Sprite* sprite) override {/* does nothing*/};
    void        setDestroy() override;
    void        handleClick(int xPosition, int yPosition) override;
    bool        drop() override;
};
