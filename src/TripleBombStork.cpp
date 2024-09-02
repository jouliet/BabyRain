#include "TripleBombStork.hpp"

TripleBombStork::TripleBombStork(b2World* world, std::vector<std::unique_ptr<Sprite>>* sprites) : Stork(world) {
    dropPoint = randomDrop();
    dropClock.restart();

    for (int i = 1; i < 4; i++)
    {
        auto baby = std::make_unique<TripleBomb>(world, bodyDef.position.x, bodyDef.position.y, bodyDef.linearVelocity.x, i);
        children.push_back(baby.get());
        sprites->push_back(std::move(baby));
    }

}

void TripleBombStork::update(bool movingLeft, bool movingRight) {
    if (!isDropping && dropClock.getElapsedTime().asSeconds() > dropPoint) {
        for (auto const &child : children)
        {
            child->drop();
        }
        isDropping = true;
    }

    b2Vec2 position = body->GetPosition();
    if (position.x < -10.f - halfWidth)
    {
        setDestroy();
    }
    if (position.x > 10.f + halfWidth)
    {
        setDestroy();
    }

    rec.setPosition(300 + position.x * scale, 300.0f - (position.y * scale));
}

float TripleBombStork::randomDrop() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1, 7);

    return static_cast<float>(dis(gen));
}