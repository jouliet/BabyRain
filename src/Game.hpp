#include "SFML/Graphics.hpp"

class Game
{
private:
    void					processEvents();
	//void					update(sf::Time elapsedTime);
	void					render();


    sf::RenderWindow		window{sf::VideoMode{640, 480}, "Baby Rain", sf::Style::Close};
	static const sf::Time	TimePerFrame;
    
public:
            Game();
    void    run();
};
