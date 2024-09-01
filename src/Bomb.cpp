#include "Bomb.hpp"

Bomb::Bomb(b2World* world, float xPosition, float yPosition, float initialSpeed) {
    //box2d
    bodyDef.type = b2_kinematicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(xPosition, yPosition - halfHeight - 0.5f);
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
    rec.setFillColor(sf::Color::Black);

    point = -2;
    dropPoint = randomDrop();
    dropClock.restart();
}

void Bomb::draw(sf::RenderWindow& window) const {
    window.draw(rec);
}

void Bomb::update(bool movingLeft, bool movingRight) {
    b2Vec2 position = body->GetPosition();

    if (position.y < -6) {
        setDestroy();
    }

    if (!isDropping && dropClock.getElapsedTime().asSeconds() > dropPoint) {
        body->SetLinearVelocity((b2Vec2){0, speed});
        isDropping = true;
    }
    
    rec.setPosition(300 + position.x * scale, 300.0f - (position.y * scale));   
}

void Bomb::setDestroy() {
    destroy = true;
}

bool Bomb::drop() {
    return false;
}

float Bomb::randomDrop() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1, 7);

    return static_cast<float>(dis(gen));
}