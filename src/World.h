#pragma once
#include <SFML/Graphics.hpp>
#include "configuration.hpp"
#include "Player.h"
#include "Enemy.h"

class World
{
 public:
	World();
	~World();

	sf::Vector2f mapSize = {1000, 1000};
	sf::Color background_color = {125, 220, 130};
	sf::RectangleShape background{mapSize};
	sf::View camera{sf::Vector2f(conf::window_size_f) / 2.0f, sf::Vector2f(conf::window_size)};
	Player* player;
	std::vector<Enemy*> enemies;

	void draw(sf::RenderWindow *window);
	void update(float dt, sf::RenderWindow *window);
	void center_camera();
};
