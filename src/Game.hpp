#include "SFML/Graphics.hpp"
#include <Box2d/Box2d.h>
#include <memory>
#include <iostream>
#include "Sprite.hpp"
#include "StaticSprite.hpp"
#include "Stroller.hpp"
#include "Baby.hpp"
#include "ContactListener.hpp"
#include "Fixtures.hpp"

class Game 
{
private:
    void					processEvents();
	void					update();
	void					render();

    void                    handleInput(sf::Keyboard::Key key, bool isPressed);

    sf::RenderWindow		window{sf::VideoMode{600, 600}, "Baby Rain", sf::Style::Close};
	static const sf::Time	TimePerFrame;
    const float             scale = 30;
    int32                   velocityIterations = 6;
    int32                   positionIterations = 2;

    b2World                                 world;
    std::vector<std::unique_ptr<Sprite>>    sprites;

    bool					movingRight{false};
    bool					movingLeft{false};
    
    std::unique_ptr<ContactListener>                    contactListener;
    sf::Clock               babySpawnClock;
    sf::Clock               playerClock;

    bool                    gameRunning;
public:
            Game();
            ~Game();
    void    run();

    void    addFixtureUserData(std::unique_ptr<MyFixtureUserData> data);
    void    stopGame();
    void    restartGame();
};
