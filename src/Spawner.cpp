#include "Spawner.hpp"

std::unique_ptr<Sprite> Spawner::randomStork(b2World* world, std::vector<std::unique_ptr<Sprite>>* sprites) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1,3);
    int random = dis(gen);

    switch (random)
    {
    case 1:
        return std::make_unique<BabyStork>(world, sprites);
        break;
    
    case 2:
        return std::make_unique<BombStork>(world, sprites);
        break;

    case 3:
        return std::make_unique<TripleBombStork>(world, sprites);
    
    default:
        return std::make_unique<BabyStork>(world, sprites);
        break;
    }
}