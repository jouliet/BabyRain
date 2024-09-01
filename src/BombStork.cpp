#include "BombStork.hpp"

BombStork::BombStork(b2World* world, std::vector<std::unique_ptr<Sprite>>* sprites) : Stork(world) {
    dropPoint = randomDrop();
    dropClock.restart();

    auto baby = std::make_unique<Bomb>(world, bodyDef.position.x, bodyDef.position.y, bodyDef.linearVelocity.x);
    child = baby.get();
    sprites->push_back(std::move(baby));
}

void BombStork::update(bool movingLeft, bool movingRight) {
    if (!isDropping && dropClock.getElapsedTime().asSeconds() > dropPoint) {
        child->drop();
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

float BombStork::randomDrop() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1, 7);

    return static_cast<float>(dis(gen));
}