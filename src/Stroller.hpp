#pragma once
#include "Sprite.hpp"
#include <SFML/Audio.hpp>

class Stroller : public Sprite
{
private:
    float               halfHeight{1.5};
    float               halfWidth{1.5};       
    b2Vec2              force{50, 0};
    int                 score{0};

    b2FixtureDef                           fixtureDef;
    std::unique_ptr<MyFixtureUserData>     fixtureUserData;

    sf::Text            scoreDisplay;
    sf::Font            font;

public:
    explicit    Stroller(b2World* world, float xPosition, float yPosition);

    void        draw(sf::RenderWindow& window) const override;
    void        update(bool movingLeft, bool movingRight) override;
    void        handleCollision(Sprite* sprite) override;
    void        setDestroy() override;
    void        handleClick(int xPosition, int yPosition) override {/* does nothing */};
    bool        drop() override;
};
