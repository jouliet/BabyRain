#include "BabyStork.hpp"

BabyStork::BabyStork(b2World* world, std::vector<std::unique_ptr<Sprite>>* sprites) : Stork(world) {
    auto baby = std::make_unique<Baby>(world, bodyDef.position.x, bodyDef.position.y, bodyDef.linearVelocity.x);
    child = baby.get();
    sprites->push_back(std::move(baby));
}

void BabyStork::handleClick(int xPosition, int yPosition) {
    if (rec.getGlobalBounds().contains(static_cast<float>(xPosition), static_cast<float>(yPosition)))
    {
        child->drop();
        setDestroy();
    }
}