#pragma once
#include <SFML/Graphics.hpp>

class Player
{
 public:
	sf::CircleShape body;
	int health = 2000;
	float speed = 100;
	float radius = 30;
	Player();
	void draw(sf::RenderWindow *window);
	void update(float dt);
};