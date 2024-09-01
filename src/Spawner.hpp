#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Sprite.hpp"
#include "Stork.hpp"
#include "BabyStork.hpp"
#include "BombStork.hpp"
#include <random>

class Spawner
{
public:
    Spawner() = default;
    
    std::unique_ptr<Sprite>     randomStork(b2World* world, std::vector<std::unique_ptr<Sprite>>* sprites) const;

};
