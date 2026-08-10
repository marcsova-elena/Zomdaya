#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Gun
{
 public:
	sf::RectangleShape body;
	sf::Vector2f size = {5, 7};
	sf::Color color = {220, 220, 220};

	int capacity = 12;
	float reloadSpeed = 3;
	float fireSpeed = 0.2f;
	float shootTimer = 0.0f;
	float damage = 200;

	Gun();
	~Gun();
	void shoot(std::vector<Bullet*> *bullets, sf::Vector2f pos, sf::Vector2f dir);
};
