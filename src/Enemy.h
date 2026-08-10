#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
 public:
	sf::CircleShape body;
	int health = 500;
	float speed = 100;
	float radius = 25;
	bool isAlive = true;
	Enemy();
	void draw(sf::RenderWindow *window);
	void update(float dt, sf::Vector2f playerPos);
	void damage(float damage);
 private:
 	void move(sf::Vector2f pos);
};