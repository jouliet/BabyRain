#include "Stroller.hpp"

Stroller::Stroller(b2World* world, float height, float width, float xPosition, float yPosition) {
    //box2d
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(xPosition, yPosition);
    body = world->CreateBody(&bodyDef);
    box.SetAsBox(width, height);
    fixtureDef.shape = &box;
    fixtureDef.density = 5.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    //sfml
    rec.setSize(sf::Vector2f(2 * width * scale, 2 * height * scale));
    rec.setOrigin(rec.getSize()/2.f);
    rec.setPosition(300 + bodyDef.position.x * scale, 300.0f - (bodyDef.position.y * scale));
    rec.setFillColor(sf::Color::Cyan);
}

void Stroller::draw(sf::RenderWindow& window) const {
    window.draw(rec);
}

void Stroller::update() {
    rec.setPosition(300 + body->GetPosition().x * scale, 300.0f - (body->GetPosition().y * scale));
}