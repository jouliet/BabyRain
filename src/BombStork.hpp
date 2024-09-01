#pragma once
#include "Sprite.hpp"
#include "Stork.hpp"
#include "Bomb.hpp"

class BombStork : public Stork
{
private:
    float       halfHeight{1.f};
    float       halfWidth{1.f};
    float       speed{2.f};

    b2FixtureDef                            fixtureDef;
    std::unique_ptr<MyFixtureUserData>      fixtureUserData;

    Sprite*                                 child;
public:
    BombStork(b2World* world, std::vector<std::unique_ptr<Sprite>>* sprites);
};


