#include "SFML/Graphics.hpp"
#include <Box2d/Box2d.h>
#include <memory>
#include <iostream>

#include "Sprite.hpp"
#include "StaticSprite.hpp"
#include "Stroller.hpp"
#include "Baby.hpp"
#include "Stork.hpp"

#include "ContactListener.hpp"
#include "Fixtures.hpp"
#include "SoundManager.hpp"
#include "Spawner.hpp"

class Game 
{
private:
    void					processEvents();
	void					update();
	void					render();
    void                    cleanUp();

    void                    handleInput(sf::Keyboard::Key key, bool isPressed);
    void                    handleClick(sf::Mouse::Button button, int xPosition, int yPosition);

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

    sf::Clock               storkSpawnClock;

    sf::Clock               playerClock;
    sf::Time                gameTime;
    sf::Font                font;
    sf::Text                timeDisplay;

    bool                    gameRunning;

    SoundManager            soundManager;
    
    Spawner                 spawner;

    sf::Texture             backgroundTexture;
    sf::Sprite              backgroundSprite;

    sf::Texture             cursorTexture;
    sf::RectangleShape      cursor;

public:
                            Game();
                            ~Game();
    void                    run();

    void                    stopGame();
    void                    restartGame();
};
