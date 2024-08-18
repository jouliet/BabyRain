#include "Stroller.hpp"

Stroller::Stroller(b2WorldId worldId, float height, float width, float xPosition, float yPosition) {
    //box2d
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position = (b2Vec2){xPosition, yPosition};
    //data->type = 1;
    //data->sprite = this;
    bodyDef.userData = this;
    bodyId = b2CreateBody(worldId, &bodyDef);
    box = b2MakeBox(width, height);
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    shapeDef.enableContactEvents = true;
    b2CreatePolygonShape(bodyId, &shapeDef, &box);

    //sfml
    rec.setSize(sf::Vector2f(2 * width * scale, 2 * height * scale));
    rec.setOrigin(rec.getSize()/2.f);
    rec.setPosition(300 + bodyDef.position.x * scale, 300.0f - (bodyDef.position.y * scale));
    rec.setFillColor(sf::Color::Cyan);
    if (!texture.loadFromFile("resources/stroller.png")) {
        std::cerr << "fail texture" << std::endl;
    }
    rec.setTexture(&texture);
}

void Stroller::draw(sf::RenderWindow& window) const {
    window.draw(rec);
}

void Stroller::update(bool movingLeft, bool movingRight) {
    float left = -10 + rec.getSize().x/(2*scale);
    float right = 10 - rec.getSize().x/(2*scale);
    
    if (movingLeft)
    {
        b2Body_ApplyForceToCenter(bodyId, -force, true);
    }
    if (movingRight)
    {
        b2Body_ApplyForceToCenter(bodyId, force, true);
    }

    b2Vec2 position = b2Body_GetPosition(bodyId);
    if (position.x < left) {
        b2Body_SetTransform(bodyId, b2Vec2{left, position.y}, b2Body_GetRotation(bodyId));
        b2Body_SetLinearVelocity(bodyId, b2Vec2{0.0f, 0.0f});
    }
    if (position.x > right) {
        b2Body_SetTransform(bodyId, b2Vec2{right, position.y}, b2Body_GetRotation(bodyId));
        b2Body_SetLinearVelocity(bodyId, b2Vec2{0.0f, 0.0f});
    } 
    
    rec.setPosition(300 + position.x * scale, 300.0f - (position.y * scale));
}

void Stroller::handleCollision(Sprite* sprite) {
    sprite->setDestroy();
}

void Stroller::setDestroy() {
    // cant be destroyed
}