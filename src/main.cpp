#include <SFML/Graphics.hpp>
#include "events.hpp"
#include "configuration.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode({conf::window_size.x, conf::window_size.y}), "Space");
	window.setFramerateLimit(conf::max_framerate);
	
	sf::Clock deltaClock;

    while(window.isOpen())
    {
		sf::Time dt = deltaClock.restart();
		processEvents(window);
		
		window.clear();
		window.display();
    }

    return 0;
}
