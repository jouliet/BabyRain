#include "Baby.hpp"
#include "iostream"
#include "Fixtures.hpp"

Baby::Baby(b2WorldId worldId, float height, float width) {
    //box2d
    bodyDef.type = b2_kinematicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position = (b2Vec2){randomPosition(), 11.f};
    bodyDef.linearVelocity = (b2Vec2){0.0f, -1.f};
    //data->type = 2;
    //data->sprite = this;
    bodyDef.userData = this;
    bodyId = b2CreateBody(worldId, &bodyDef);
    box = b2MakeBox(width, height);
    shapeDef.density = 0.4f;
    shapeDef.friction = 0.3f;
    shapeDef.enableContactEvents = true;
    b2CreatePolygonShape(bodyId, &shapeDef, &box);
    
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
    b2Vec2 position = b2Body_GetPosition(bodyId);
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