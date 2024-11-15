#include "StaticSprite.hpp"
#include <iostream>

StaticSprite::StaticSprite(b2World* world, float height, float width, float xPosition, float yPosition) {
    //box2d
    bodyDef.position.Set(xPosition, yPosition);
    bodyDef.type = b2_staticBody;
    body = world->CreateBody(&bodyDef);
    box.SetAsBox(width, height);
    body->CreateFixture(&box, 0.0f);
    //sfml
    rec.setSize(sf::Vector2f(2 * width * scale, 2 * height * scale));
    rec.setOrigin(rec.getSize()/2.f);
    rec.setPosition(300 + bodyDef.position.x * scale, 300.0f - (bodyDef.position.y * scale));
    rec.setFillColor(sf::Color::Green);
}

void StaticSprite::draw(sf::RenderWindow& window) const {
    window.draw(rec);
}

void StaticSprite::update(bool movingLeft, bool movingRight) {
    //static donc rien
}

void StaticSprite::handleCollision(Sprite* sprite) {
    //TODOS
}

void StaticSprite::setDestroy() {
    //ne fait rien
}

bool StaticSprite::drop() {
    return false;
}