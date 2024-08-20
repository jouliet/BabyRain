#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game() : world{(b2Vec2){0.0f, -10.0f}}, gameRunning{true} {
	if (!soundManager.loadSound("resources/sujet_micro-projet_CSC4526_2023_2024.wav")) {
		std::cout << "Error loading sound file" << std::endl;
	}
	if (!backgroundTexture.loadFromFile("resources/bg.jpg")) {
    std::cerr << "Failed to load background image!" << std::endl;
	}
	backgroundSprite.setTexture(backgroundTexture);
	font.loadFromFile("resources/arial.ttf");
	timeDisplay.setFont(font);
    timeDisplay.setCharacterSize(25);
    timeDisplay.setFillColor(sf::Color::Black);
    timeDisplay.setPosition(10.f, 10.f);

	contactListener = std::make_unique<ContactListener>();
	world.SetContactListener(contactListener.get());

    sprites.push_back(std::make_unique<StaticSprite>(&world, 2.0f, 10.0f, 0.0f, -8.0f));
    sprites.push_back(std::make_unique<Stroller>(&world, 1.0f, 1.0f, 0.0f, 0.0f));
	//sprites.push_back(std::make_unique<Baby>(&world, 1.0f, 0.5f));
	sprites.push_back(std::make_unique<Stork>(&world));

	playerClock.restart();
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

		case sf::Event::MouseButtonPressed:
			handleClick(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
			break;

		default:
			break;
		}
	}
}

void Game::update() {
	if (gameRunning) {
        gameTime = playerClock.getElapsedTime();
    }
	timeDisplay.setString("Time: " + std::to_string(gameTime.asSeconds()));

	cleanUp();

    for (const auto& sprite : sprites)
    {
        sprite->update(movingLeft, movingRight);
		if (sprite->destroy)
		{
			soundManager.playSound();
			stopGame();
		}	
    }

	/* if (storkSpawnClock.getElapsedTime().asSeconds() >= 3.5f) {
        sprites.push_back(std::make_unique<Stork>(&world));
        storkSpawnClock.restart();
    } */
}

void Game::render() {
	window.clear();
	window.draw(backgroundSprite);
    for (const auto& sprite : sprites)
    {
        sprite->draw(window);
    }
	window.draw(timeDisplay);
	window.display();
}

void Game::handleInput(sf::Keyboard::Key key, bool isPressed) {	
	if (key == sf::Keyboard::Left)
		movingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
		movingRight = isPressed;
	else if (key == sf::Keyboard::R)
		restartGame();
}

void Game::handleClick(sf::Mouse::Button button, int xPosition, int yPosition) {	
	if (button == sf::Mouse::Left) {
		for (const auto& sprite : sprites) {
			sprite->handleClick(xPosition, yPosition);
		}
	}
}

void Game::stopGame() {
    gameRunning = false;
}

void Game::restartGame() {
	//todo
	for (const auto& sprite : sprites) {
        world.DestroyBody(sprite->body);
    }
    sprites.clear();

    contactListener = std::make_unique<ContactListener>();
	world.SetContactListener(contactListener.get());

    sprites.push_back(std::make_unique<StaticSprite>(&world, 2.0f, 10.0f, 0.0f, -8.0f));
    sprites.push_back(std::make_unique<Stroller>(&world, 1.0f, 1.0f, 0.0f, 0.0f));
    //sprites.push_back(std::make_unique<Baby>(&world, 1.0f, 0.5f));

	playerClock.restart();

    gameRunning = true;
}

void Game::cleanUp() {
	for (int i = 0; i < sprites.size(); i++) {
        if (sprites[i]->destroy) {
			world.DestroyBody(sprites[i]->body);
            sprites.erase(sprites.begin() + i);
			break;
        }
    }
}