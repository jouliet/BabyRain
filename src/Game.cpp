#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game() : world{(b2Vec2){0.0f, -10.0f}}, gameRunning{true} {
	//soundManager.loadSound("baby_cry", "sujet_micro-projet_CSC4526_2023_2024.mp3");
	contactListener = std::make_unique<ContactListener>();
	world.SetContactListener(contactListener.get());
    sprites.push_back(std::make_unique<StaticSprite>(&world, 2.0f, 10.0f, 0.0f, -8.0f));
    sprites.push_back(std::make_unique<Stroller>(&world, 1.0f, 1.0f, 0.0f, 0.0f));
	sprites.push_back(std::make_unique<Baby>(&world, 1.0f, 0.5f));
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
		if (!gameRunning)
		{
			sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    restartGame();
                }
            }
            continue;
		}
		
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

void Game::update() {
	for (int i = 0; i < sprites.size(); i++) {
        if (sprites[i]->destroy) {
			world.DestroyBody(sprites[i]->body);
            sprites.erase(sprites.begin() + i);
			break;
        }
    }
    for (const auto& sprite : sprites)
    {
        sprite->update(movingLeft, movingRight);
		if (sprite->destroy)
		{
			stopGame();
		}
			
    }
	if (babySpawnClock.getElapsedTime().asSeconds() >= 3.5f) {
        sprites.push_back(std::make_unique<Baby>(&world, 1.0f, 0.5f));
        babySpawnClock.restart();
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
	else if (key == sf::Keyboard::R)
		restartGame();
	//else if (key == sf::Keyboard::P)
		//soundManager.playSound("baby_cry");
}

void Game::stopGame() {
    gameRunning = false;
}

void Game::restartGame() {
	for (const auto& sprite : sprites) {
        world.DestroyBody(sprite->body);
    }
    sprites.clear();
    contactListener = std::make_unique<ContactListener>();
	world.SetContactListener(contactListener.get());
    sprites.push_back(std::make_unique<StaticSprite>(&world, 2.0f, 10.0f, 0.0f, -8.0f));
    sprites.push_back(std::make_unique<Stroller>(&world, 1.0f, 1.0f, 0.0f, 0.0f));
    sprites.push_back(std::make_unique<Baby>(&world, 0.5f, 0.5f));
    gameRunning = true;
}