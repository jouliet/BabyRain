#include "SFML/Graphics.hpp"
#include <Box2d/Box2d.h>
#include <memory>
#include <iostream>
#include "Sprite.hpp"
#include "StaticSprite.hpp"
#include "Stroller.hpp"

class Game
{
private:
    void					processEvents();
	void					update() const;
	void					render();


    sf::RenderWindow		window{sf::VideoMode{600, 600}, "Baby Rain", sf::Style::Close};
	static const sf::Time	TimePerFrame;
    const float             scale = 30;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    b2World world;
    std::vector<std::unique_ptr<Sprite>> sprites;

public:
            Game();
            ~Game();
    void    run();
};
