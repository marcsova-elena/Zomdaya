#pragma once
#include <SFML/Graphics.hpp>
#include "Gun.h"
#include <vector>

class Player
{
 public:
	sf::CircleShape body;
	int health = 2000;
	float speed = 250;
	float radius = 25;
	float mass = 70;
	float acceleration = 15;
	float friction = 10;
	bool isAlive = true;
	sf::Vector2f velocity;
	std::vector<Bullet*> bullets;
	Gun gun;
	
	Player();
	~Player();
	void draw(sf::RenderWindow *window);
	void update(float dt, sf::RenderWindow* window);
	void move(sf::Vector2f pos_shift);
	void damage(float damage);
 private:
	bool leftClickPressed = false;
};