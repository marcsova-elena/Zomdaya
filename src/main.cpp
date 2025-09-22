#include "events.hpp"
#include "configuration.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include "Player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({conf::window_size.x, conf::window_size.y}), "Zombdaya");
	window.setFramerateLimit(conf::max_framerate);

	sf::Clock deltaClock;

	sf::RectangleShape rectangle({conf::window_size_f.x, conf::window_size_f.y});
	sf::Color background_color = {125, 220, 130};
	rectangle.setFillColor(background_color);

	Player* player = new Player();

    while(window.isOpen())
    {
		float dt = deltaClock.restart().asSeconds();
		processEvents(window);
		

		window.clear();

		window.draw(rectangle);
		player->draw(&window);

		window.display();
    }

    return 0;
}
