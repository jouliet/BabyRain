#include "TripleBomb.hpp"

TripleBomb::TripleBomb(b2World* world, float xPosition, float yPosition, float initialSpeed, int number) : Bomb(world, xPosition, yPosition, initialSpeed) {
    point = -1;
    type = number;
    rec.setFillColor(sf::Color::Cyan);

    switch (number)
    {
    case 1:
        body->SetTransform(body->GetPosition(), -3 * M_PI/4);
        rec.setRotation(45);
        break;
    
    case 3:
        body->SetTransform(body->GetPosition(), -M_PI/4);
        rec.setRotation(315);
        break;

    default:
        body->SetTransform(body->GetPosition(), -M_PI/2);
        rec.setRotation(0);
        break;
    }
}

bool TripleBomb::drop() {
    switch (type)
    {
    case 1:
        body->SetLinearVelocity((b2Vec2){-speed, -speed});
        return true;
        break;
    
    case 3:
        body->SetLinearVelocity((b2Vec2){speed, -speed});
        return true;
        break;

    default:
        body->SetLinearVelocity((b2Vec2){0, -speed});
        return true;
        return true;
        break;
    }
    return false;
}

void TripleBomb::handleClick(int xPosition, int yPosition) {
    if (body->GetLinearVelocity().y != 0 && rec.getGlobalBounds().contains(static_cast<float>(xPosition), static_cast<float>(yPosition)))
    {
        setDestroy();
    }
}

void TripleBomb::handleCollision(Sprite* sprite) {
    if (sprite->point == 1) {
        explode = true;
        setDestroy();
        sprite->setDestroy();
        gameOver = true;
    }
}