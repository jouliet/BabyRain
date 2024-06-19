#pragma once
#include <Box2D/Box2D.h>

class Sprite;

struct MyFixtureUserData {
    int type;
    Sprite* sprite;
};
