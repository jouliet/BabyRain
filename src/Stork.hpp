#pragma once
#include "Sprite.hpp"
#include "Baby.hpp"
#include <random>

class Stork : public Sprite
{
private:
    float       halfHeight{1.f};
    float       halfWidth{1.f};
    float       speed{2.f};

    b2FixtureDef                            fixtureDef;
    std::unique_ptr<MyFixtureUserData>      fixtureUserData;

    Sprite*                                 child;           

public:
    explicit    Stork(b2World* world);

    b2Vec2      randomPosition() const;

    void        draw(sf::RenderWindow& window) const override;
    void        update(bool movingLeft, bool movingRight) override;
    void        handleCollision(Sprite* sprite) override;
    void        setDestroy() override;
    void        handleClick(int xPosition, int yPosition) override;
    bool        drop() override;
};
