#include "Enemy.h"
#include "configuration.hpp"
#include <math.h>

Enemy::Enemy(sf::Vector2f pos)
{
	body.setOrigin({radius, radius});
	body.setRadius(radius);
	body.setPosition(pos);
	body.setFillColor(sf::Color::Red);
}

void Enemy::draw(sf::RenderWindow* window)
{
	window->draw(body);
}

void Enemy::update(float dt, sf::Vector2f playerPos)
{	
	// Def needs revision lol
	if(seesPlayer)
	{
		sf::Vector2f diff = playerPos - body.getPosition();
		if(diff.lengthSquared() > 0.001f)	// To reduce twitching when no change in position
		{
			sf::Vector2f dir = diff.normalized();
			sf::Vector2f targetVelocity = dir * speed;

			velocity += (targetVelocity - velocity) * acceleration * dt;
			body.setRotation(dir.angle());
			move(velocity * dt);
		}
	}
}

void Enemy::damage(float damage)
{
	health -= damage;
	if(health < 0)
	{
		isAlive = false;
	}
}

void Enemy::move(sf::Vector2f pos_shift)
{
	if(pos_shift.x == 0 && pos_shift.y == 0) return;
	body.move(pos_shift);
}