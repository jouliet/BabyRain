#include "ContactListener.hpp"
#include <iostream>
#include "Fixtures.hpp"

void ContactListener::BeginContact(b2Contact* contact) {
	b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    
    b2World* world = fixtureA->GetBody()->GetWorld();

    auto* userDataA = reinterpret_cast<MyFixtureUserData*>(fixtureA->GetUserData().pointer);
    auto* userDataB = reinterpret_cast<MyFixtureUserData*>(fixtureB->GetUserData().pointer);

    if (userDataA && userDataB)
    {
        userDataA->sprite->handleCollision(userDataB->sprite);
        userDataB->sprite->handleCollision(userDataA->sprite);
    } 
    
}