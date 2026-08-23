#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
 public:
	sf::CircleShape body;
	int health = 500;
	float speed = 100;
	float radius = 25;
	float mass = 70;
	float acceleration = 25;
	float friction = 20;
	sf::Vector2f velocity;
	bool isAlive = true;
	bool seesPlayer = true;

	Enemy(sf::Vector2f pos);
	void draw(sf::RenderWindow *window);
	void update(float dt, sf::Vector2f playerPos);
	void damage(float damage);
	void move(sf::Vector2f pos);
};