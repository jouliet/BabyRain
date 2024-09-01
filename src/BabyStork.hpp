#pragma once
#include "Sprite.hpp"
#include "Stork.hpp"
#include "Baby.hpp"

class BabyStork : public Stork
{
private:
    float       halfHeight{1.f};
    float       halfWidth{1.f};
    float       speed{2.f};

    b2FixtureDef                            fixtureDef;
    std::unique_ptr<MyFixtureUserData>      fixtureUserData;

    Sprite*                                 child;
public:
    BabyStork(b2World* world, std::vector<std::unique_ptr<Sprite>>* sprites);

    void        handleClick(int xPosition, int yPosition) override;
};