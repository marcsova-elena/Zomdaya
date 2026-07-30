#include <vector>
#include "World.h"
#include "events.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode({conf::window_size.x, conf::window_size.y}), "Zombdaya");
	window.setFramerateLimit(conf::max_framerate);

	sf::Clock deltaClock;

	World* world = new World();

    while(window.isOpen())
    {
		float dt = deltaClock.restart().asSeconds();
		processEvents(window);

		
		window.clear();

		world->update(dt, &window);

		window.setView(world->camera);
		
		world->draw(&window);

		window.display();
    }

	delete world;

    return 0;
}
