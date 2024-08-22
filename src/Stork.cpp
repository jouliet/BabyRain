#include "Stork.hpp"

Stork::Stork(b2World* world, std::vector<std::unique_ptr<Sprite>>* sprites) {
    //box2d
    bodyDef.type = b2_kinematicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(randomPosition().x, randomPosition().y);
    if (bodyDef.position.x <= 0)
    {
        bodyDef.linearVelocity.Set(speed, 0.0f);
    } else {
        bodyDef.linearVelocity.Set(-speed, 0.0f);
    }
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
    if (!texture.loadFromFile("resources/stork.png")) {
        std::cerr << "fail loading texture" << std::endl;
    }
    rec.setTexture(&texture);
    if (bodyDef.linearVelocity.x < 0)
    {
        rec.setScale(-1, 1);
    }
    

    auto baby = std::make_unique<Baby>(world, bodyDef.position.x, bodyDef.position.y, bodyDef.linearVelocity.x);
    child = baby.get();
    sprites->push_back(std::move(baby));
}

void Stork::draw(sf::RenderWindow& window) const {
    window.draw(rec);
}

void Stork::update(bool movingLeft, bool movingRight) {
    b2Vec2 position = body->GetPosition();
    if (position.x < -10.f - halfWidth)
    {
        setDestroy();
        child->setDestroy();
    }
    if (position.x > 10.f + halfWidth)
    {
        setDestroy();
        child->setDestroy();
    }

    rec.setPosition(300 + position.x * scale, 300.0f - (position.y * scale));
}

void Stork::handleCollision(Sprite* sprite) {
    //no collisions
}

void Stork::handleClick(int xPosition, int yPosition) {
    if (rec.getGlobalBounds().contains(static_cast<float>(xPosition), static_cast<float>(yPosition)))
    {
        setDestroy();
        child->drop();
    }
}

void Stork::setDestroy() {
    destroy = true;
}

b2Vec2 Stork::randomPosition() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> x(0.f, 1);
    std::uniform_real_distribution<> y(0.f, 8.0);

    if (x(gen) == 0) {
        return b2Vec2{-10 - halfWidth, static_cast<float>(y(gen))};
    } else {
        return b2Vec2{10 + halfWidth, static_cast<float>(y(gen))};
    }
    
}