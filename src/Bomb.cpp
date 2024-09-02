#include "Bomb.hpp"

Bomb::Bomb(b2World* world, float xPosition, float yPosition, float initialSpeed) {
    //box2d
    bodyDef.type = b2_kinematicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(xPosition, yPosition - halfHeight - 0.1f);
    bodyDef.linearVelocity.Set(initialSpeed, 0);
    body = world->CreateBody(&bodyDef);

    box.SetAsBox(halfWidth, halfHeight);
    fixtureDef.shape = &box;
    fixtureDef.density = 0.1f;
    fixtureDef.friction = 0.3f;

    fixtureUserData = std::make_unique<MyFixtureUserData>();
    fixtureUserData->type = 1;
    fixtureUserData->sprite = this;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(fixtureUserData.get());

    body->CreateFixture(&fixtureDef);
    
    //sfml
    rec.setSize(sf::Vector2f(2 * halfWidth * scale, 2 * halfHeight * scale));
    rec.setOrigin(rec.getSize()/2.f);
    rec.setPosition(300 + bodyDef.position.x * scale, 300.0f - (bodyDef.position.y * scale));
    if (!texture.loadFromFile("resources/bomb.png")) {
        std::cerr << "failed to load texture" << std::endl;
    }
    rec.setTexture(&texture);
    rec.setRotation(90);
    body->SetTransform(body->GetPosition(), M_PI/2);

    point = -3;
}

void Bomb::draw(sf::RenderWindow& window) const {
    window.draw(rec);
}

void Bomb::update(bool movingLeft, bool movingRight) {
    b2Vec2 position = body->GetPosition();

    if (position.y - halfHeight < -6) {
        explode = true;
        setDestroy();
    }
    if (position.x < -12.f - halfWidth)
    {
        setDestroy();
    }
    if (position.x > 12.f + halfWidth)
    {
        setDestroy();
    }
    
    rec.setPosition(300 + position.x * scale, 300.0f - (position.y * scale));   
}

void Bomb::setDestroy() {
    destroy = true;
}

bool Bomb::drop() {
    body->SetLinearVelocity((b2Vec2){0, speed});
    body->SetTransform(body->GetPosition(), -M_PI/2);
    rec.setRotation(0);
    return true;
}

void Bomb::handleClick(int xPosition, int yPosition) {
    if (body->GetLinearVelocity().y == speed && rec.getGlobalBounds().contains(static_cast<float>(xPosition), static_cast<float>(yPosition)))
    {
        setDestroy();
    }
}