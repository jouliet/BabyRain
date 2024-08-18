#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game() {
	//set world
	worldId = b2CreateWorld(&worldDef);

	//set resources
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

    sprites.push_back(std::make_unique<StaticSprite>(worldId, 2.0f, 10.0f, 0.0f, -8.0f));
    sprites.push_back(std::make_unique<Stroller>(worldId, 1.0f, 1.0f, 0.0f, 0.0f));
	sprites.push_back(std::make_unique<Baby>(worldId, 1.0f, 0.5f));

	playerClock.restart();
}

Game::~Game()
{
	//b2DestroyWorld(worldId);
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
            b2World_Step(worldId, timeStep, subStepCount);
			processCollisions();
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

void Game::processCollisions() {
	b2ContactEvents contactEvents = b2World_GetContactEvents(worldId);
	for (int i = 0; i < contactEvents.beginCount; ++i)
	{
		std::cout << "collision happened" << std::endl;
		b2ContactBeginTouchEvent* beginEvent = contactEvents.beginEvents + i;
		auto spriteA = static_cast<Sprite*>(b2Body_GetUserData(b2Shape_GetBody(beginEvent->shapeIdA)));
		auto spriteB = static_cast<Sprite*>(b2Body_GetUserData(b2Shape_GetBody(beginEvent->shapeIdB)));
		if (spriteA && spriteB) {
			spriteA->handleCollision(spriteB);
			spriteB->handleCollision(spriteA);
		}
	}
}

void Game::update() {
	if (gameRunning) {
        elapsedTime = playerClock.getElapsedTime();
    }
	timeDisplay.setString("Time: " + std::to_string(elapsedTime.asSeconds()));

	for (int i = 0; i < sprites.size(); i++) {
        if (sprites[i]->destroy) {
			b2DestroyBody(sprites[i]->bodyId);
            sprites.erase(sprites.begin() + i);
			break;
        }
    }
    for (const auto& sprite : sprites)
    {
        sprite->update(movingLeft, movingRight);
		if (sprite->destroy)
		{
			soundManager.playSound();
			stopGame();
		}
			
    }
	/* if (babySpawnClock.getElapsedTime().asSeconds() >= 3.5f) {
        sprites.push_back(std::make_unique<Baby>(worldId, 1.0f, 0.5f));
        babySpawnClock.restart();
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

void Game::stopGame() {
    gameRunning = false;
}

void Game::restartGame() {
	for (const auto& sprite : sprites) {
        b2DestroyBody(sprite->bodyId);
    }
    sprites.clear();
    sprites.push_back(std::make_unique<StaticSprite>(worldId, 2.0f, 10.0f, 0.0f, -8.0f));
    sprites.push_back(std::make_unique<Stroller>(worldId, 1.0f, 1.0f, 0.0f, 0.0f));
    sprites.push_back(std::make_unique<Baby>(worldId, 1.0f, 0.5f));
	playerClock.restart();

    gameRunning = true;
}