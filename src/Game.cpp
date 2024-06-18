#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game() : world{(b2Vec2){0.0f, -10.0f}} {
    sprites.push_back(std::make_unique<StaticSprite>(&world, 2.0f, 10.0f, 0.0f, -8.0f));
    sprites.push_back(std::make_unique<Stroller>(&world, 1.0f, 1.0f, 0.0f, 0.0f));
}

Game::~Game()
{
    sprites.clear();
}

void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
            world.Step(TimePerFrame.asSeconds(), velocityIterations, positionIterations);
			update();
		}

		render();
	}
}

void Game::processEvents() {
    sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		
		case sf::Event::KeyPressed:
			handleInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handleInput(event.key.code, false);
			break;

		default:
			break;
		}
	}
}

void Game::update() const {
    for (const auto& sprite : sprites)
    {
        sprite->update(movingLeft, movingRight);
    }
    
}

void Game::render() {
	window.clear();
    for (const auto& sprite : sprites)
    {
        sprite->draw(window);
    }
	window.display();
}

void Game::handleInput(sf::Keyboard::Key key, bool isPressed) {	
	if (key == sf::Keyboard::Left)
		movingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
		movingRight = isPressed;
}