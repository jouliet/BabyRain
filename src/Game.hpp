#include "SFML/Graphics.hpp"
#include <Box2d/Box2d.h>
#include <memory>
#include <iostream>
#include "Sprite.hpp"
#include "StaticSprite.hpp"
#include "Stroller.hpp"
#include "Baby.hpp"
#include "Fixtures.hpp"
#include "SoundManager.hpp"

class Game 
{
private:
    void					                processEvents();
    void                                    processCollisions();
	void					                update();
	void					                render();

    void                                    handleInput(sf::Keyboard::Key key, bool isPressed);

    sf::RenderWindow		                window{sf::VideoMode{600, 600}, "Baby Rain", sf::Style::Close};
	static const sf::Time	                TimePerFrame;
    const float                             scale{30};
    const float                             timeStep{1.f/60.f};
    const int                               subStepCount{4};

    b2WorldDef                              worldDef{b2DefaultWorldDef()};
    b2WorldId                               worldId;

    std::vector<std::unique_ptr<Sprite>>    sprites;

    sf::Clock                               babySpawnClock;

    bool					                movingRight{false};
    bool					                movingLeft{false};
    
    SoundManager                            soundManager;

    sf::Clock                               playerClock;
    sf::Time                                elapsedTime;
    sf::Font                                font;
    sf::Text                                timeDisplay;
    sf::Texture                             backgroundTexture;
    sf::Sprite                              backgroundSprite;

    bool                                    gameRunning{true};

public:
            Game();
            ~Game();
    void    run();

    void    stopGame();
    void    restartGame();
};
