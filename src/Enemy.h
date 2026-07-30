#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
 public:
	sf::CircleShape body;
	int health = 2000;
	float speed = 100;
	float radius = 30;
	Enemy();
	void draw(sf::RenderWindow *window);
	void update(float dt, sf::Vector2f playerPos);
 private:
 	void move(sf::Vector2f pos);
};