#include "BombStork.hpp"

BombStork::BombStork(b2World* world, std::vector<std::unique_ptr<Sprite>>* sprites) : Stork(world) {
    auto baby = std::make_unique<Bomb>(world, bodyDef.position.x, bodyDef.position.y, bodyDef.linearVelocity.x);
    child = baby.get();
    sprites->push_back(std::move(baby));
}