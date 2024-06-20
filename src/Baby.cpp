#include "Baby.hpp"
#include "iostream"
#include "Fixtures.hpp"

Baby::Baby(b2World* world, float height, float width) {
    //box2d
    bodyDef.type = b2_kinematicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(randomPosition(), 11.f);
    body = world->CreateBody(&bodyDef);
    box.SetAsBox(width, height);
    fixtureDef.shape = &box;
    fixtureDef.density = 0.1f;
    fixtureDef.friction = 0.3f;
    body->SetLinearVelocity(b2Vec2(0.0f, -1.2f));
    //sfml
    rec.setSize(sf::Vector2f(2 * width * scale, 2 * height * scale));
    rec.setOrigin(rec.getSize()/2.f);
    rec.setPosition(300 + bodyDef.position.x * scale, 300.0f - (bodyDef.position.y * scale));
    rec.setFillColor(sf::Color::Magenta);
    if (!texture.loadFromFile("resources/baby.png")) {
        std::cerr << "fail texture" << std::endl;
    }
    rec.setTexture(&texture);

    auto myUserData = std::make_unique<MyFixtureUserData>();
    myUserData->type = 1;
    myUserData->sprite = this;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(myUserData.get());
    body->CreateFixture(&fixtureDef);
    mFixtureUserData.emplace_back(std::move(myUserData));
    myUserData = nullptr;
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