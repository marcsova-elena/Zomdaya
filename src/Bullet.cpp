#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir, float damage)
{
	body.setOrigin({radius, radius});
	body.setRadius(radius);
	body.setPosition(pos);
	body.setFillColor(color);
	this->dir = dir;
	this->damage = damage;
}

void Bullet::draw(sf::RenderWindow *window)
{ 
	window->draw(body);
}

void Bullet::update(float dt)
{
	//if(body.getGlobalBounds().findIntersection())
	body.move(dir * speed * dt);
}