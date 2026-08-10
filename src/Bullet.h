#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
 public:
	Bullet(sf::Vector2f pos, sf::Vector2f dir, float damage);
	
	sf::CircleShape body;
	sf::Vector2f dir;
	float radius = 5;
	float speed = 300.f;
	float damage = 200;
	bool isAlive = true;
	sf::Color color = {200, 190, 0};
	
	void draw(sf::RenderWindow *window);
	void update(float dt);
};
