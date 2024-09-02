#include "Stroller.hpp"

Stroller::Stroller(b2World* world, float xPosition, float yPosition) {
    //box2d
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(xPosition, yPosition);
    body = world->CreateBody(&bodyDef);
    
    box.SetAsBox(halfWidth, halfHeight);
    fixtureDef.shape = &box;
    fixtureDef.density = 1.0f;
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
    if (!texture.loadFromFile("resources/stroller.png")) {
        std::cerr << "fail texture" << std::endl;
    }
    rec.setTexture(&texture);

    //player score
    point = 0;
    font.loadFromFile("resources/arial.ttf");
    scoreDisplay.setFont(font);
	scoreDisplay.setCharacterSize(25);
	scoreDisplay.setFillColor(sf::Color::Red);
	scoreDisplay.setPosition(10.f, 40.f);
}

void Stroller::draw(sf::RenderWindow& window) const {
    window.draw(rec);
    window.draw(scoreDisplay);
}

void Stroller::update(bool movingLeft, bool movingRight) {
    scoreDisplay.setString("Score: " + std::to_string(score));

    float left = -10 + rec.getSize().x/(2*scale);
    float right = 10 - rec.getSize().x/(2*scale);
    
    if (movingLeft)
    {
        body->ApplyForceToCenter(-force, true);
    }
    if (movingRight)
    {
        body->ApplyForceToCenter(force, true);
    }

    b2Vec2 position = body->GetPosition();
    if (position.x < left) {
        body->SetTransform(b2Vec2(left, position.y), body->GetAngle());
        body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    }
    if (position.x > right) {
        body->SetTransform(b2Vec2(right, position.y), body->GetAngle());
        body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    }
    
    rec.setPosition(300 + position.x * scale, 300.0f - (position.y * scale));
}

void Stroller::handleCollision(Sprite* sprite) {
    if (sprite->point < 0)
    {
        sprite->explode = true;
    }
    sprite->setDestroy();
    score += sprite->point;
    if (score <= 0)
    {
        gameOver = true;
    }
}

void Stroller::setDestroy() {
    destroy = true;
}

bool Stroller::drop() {
    return false;
}