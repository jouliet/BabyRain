#include <gtest/gtest.h>
#include <string>
#include "pugixml.hpp"

#include "Sprite.hpp"
#include "Stroller.hpp"
#include "StaticSprite.hpp"
#include "Baby.hpp"
#include "ContactListener.hpp"



// Test de l'initialisation du StaticSprite
TEST(TestStaticSprite, Initialization)
{
    b2World world(b2Vec2(0.0f, 0.0f)); // Créer un monde Box2D
    StaticSprite sprite(&world, 50, 100, 200, 300); // Création du sprite statique

    // Vérifier les propriétés du body Box2D
    EXPECT_EQ(sprite.body->GetType(), b2_staticBody);
    EXPECT_FLOAT_EQ(sprite.body->GetPosition().x, 200);
    EXPECT_FLOAT_EQ(sprite.body->GetPosition().y, 300);

    // Vérifier les propriétés du rectangle SFML
    EXPECT_EQ(sprite.rec.getSize().x, 2 * 100 * sprite.scale);
    EXPECT_EQ(sprite.rec.getSize().y, 2 * 50 * sprite.scale);
    EXPECT_EQ(sprite.rec.getPosition().x, 300 + 200 * sprite.scale);
    EXPECT_EQ(sprite.rec.getPosition().y, 300 - 300 * sprite.scale);
    EXPECT_EQ(sprite.rec.getFillColor(), sf::Color::Green);
}

// Test de la mise à jour du Stroller (mouvement vers la gauche)
TEST(StrollerTest, UpdateMovingLeft) {
    b2World world(b2Vec2(0.0f, 0.0f));
    Stroller stroller(&world, 1.0f, 1.0f, 0.0f, 0.0f);

    stroller.update(true, false);
    world.Step(1.0f / 60.0f, 6, 2); // Simuler un pas de temps

    ASSERT_LT(stroller.body->GetPosition().x, 0.0f); // La position devrait être inférieure à zéro
}

// Test de la mise à jour du Stroller (mouvement vers la droite)
TEST(StrollerTest, UpdateMovingRight) {
    b2World world(b2Vec2(0.0f, 0.0f));
    Stroller stroller(&world, 1.0f, 1.0f, 0.0f, 0.0f);

    stroller.update(false, true);
    world.Step(1.0f / 60.0f, 6, 2); // Simuler un pas de temps

    ASSERT_GT(stroller.body->GetPosition().x, 0.0f); // La position devrait être supérieure à zéro
}

// Test de la mise à jour du Baby (vérification de la destruction)
TEST(BabyTest, Update) {
    b2World world(b2Vec2(0.0f, 0.0f));
    Baby baby(&world, 1.0f, 0.5f);
    // Avancer le temps pour simuler la chute
    world.Step(1.0f / 60.0f, 6, 2);
    baby.update(false, false);

    b2Vec2 position = baby.body->GetPosition();
    ASSERT_FALSE(baby.destroy);

    // Déplacer le baby en-dessous de -6 en y
    baby.body->SetTransform(b2Vec2(position.x, -7.0f), baby.body->GetAngle());
    baby.update(false, false);

    ASSERT_TRUE(baby.destroy); // Devrait être détruit
}

// Test de la gestion des collisions entre stroller et baby
TEST(BabyTest, HandleCollision) {
    b2World world(b2Vec2(0.0f, 0.0f));
    Baby baby(&world, 1.0f, 0.5f);
    Stroller stroller(&world, 1.0f, 1.0f, 0.0f, 0.0f);
    std::unique_ptr<ContactListener> contactListener = std::make_unique<ContactListener>();
    world.SetContactListener(contactListener.get());
    
    ASSERT_FALSE(baby.destroy);

    baby.body->SetTransform(b2Vec2(0.0f, 0.0f), 0.0f);
    world.Step(1.0f / 60.0f, 6, 2);
    
    ASSERT_TRUE(baby.destroy);
}