#pragma once
#include <Box2d/Box2d.h>
#include "Sprite.hpp"

class ContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact) override;
};