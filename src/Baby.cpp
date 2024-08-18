#include "Baby.hpp"
#include "iostream"

Baby::Baby(b2World* world, float height, float width) {
    //box2d
    bodyDef.type = b2_kinematicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(randomPosition(), 11.f);
    bodyDef.linearVelocity.Set(0.0f, -1.2f);
    body = world->CreateBody(&bodyDef);

    box.SetAsBox(width, height);
    fixtureDef.shape = &box;
    fixtureDef.density = 0.1f;
    fixtureDef.friction = 0.3f;

    fixtureUserData = std::make_unique<MyFixtureUserData>();
    fixtureUserData->type = 1;
    fixtureUserData->sprite = this;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(fixtureUserData.get());

    body->CreateFixture(&fixtureDef);
    
    //sfml
    rec.setSize(sf::Vector2f(2 * width * scale, 2 * height * scale));
    rec.setOrigin(rec.getSize()/2.f);
    rec.setPosition(300 + bodyDef.position.x * scale, 300.0f - (bodyDef.position.y * scale));
    rec.setFillColor(sf::Color::Magenta);
    if (!texture.loadFromFile("resources/baby.png")) {
        std::cerr << "fail texture" << std::endl;
    }
    rec.setTexture(&texture);
}

float Baby::randomPosition() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-9.0, 9.0);

    return static_cast<float>(dis(gen));
}

void Baby::draw(sf::RenderWindow& window) const {
    window.draw(rec);
}

void Baby::update(bool movingLeft, bool movingRight) {
    b2Vec2 position = body->GetPosition();
    if (position.y < -6)
    {
        destroy = true;
    }
    
    rec.setPosition(300 + position.x * scale, 300.0f - (position.y * scale));   
}

void Baby::handleCollision(Sprite* sprite) {
    //
}

void Baby::setDestroy() {
    destroy = true;
}