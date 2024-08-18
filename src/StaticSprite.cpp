#include "StaticSprite.hpp"
#include <iostream>

StaticSprite::StaticSprite(b2WorldId worldId, float height, float width, float xPosition, float yPosition) {
    //box2d
    bodyDef.position = (b2Vec2){xPosition, yPosition};
    bodyDef.userData = this;
    bodyId = b2CreateBody(worldId, &bodyDef);
    box = b2MakeBox(width, height);
    shapeDef.enableContactEvents = false;
    b2CreatePolygonShape(bodyId, &shapeDef, &box);
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
    //ne fait rien
}

void StaticSprite::setDestroy() {
    //ne peut pas être détruit
}