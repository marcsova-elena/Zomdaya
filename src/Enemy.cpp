 #include "Enemy.h"
 #include "configuration.hpp"
 #include <math.h>
 
 Enemy::Enemy()
 {
	body.setOrigin({radius / 2, radius / 2});
	body.setRadius(25);
	body.setPosition({conf::window_size_f.x / 2, conf::window_size_f.y / 2});
	body.setFillColor(sf::Color::Red);
 }

 void Enemy::draw(sf::RenderWindow* window)
 {
	window->draw(body);
 }

 void Enemy::update(float dt, sf::Vector2f playerPos)
 {
	sf::Vector2f diff = playerPos - body.getPosition();
	if(diff.lengthSquared() > 0.001f)	// To reduce twitching when no change in position
	{
		sf::Vector2f dir = diff.normalized();
		move(dir * speed * dt);

		body.setRotation(sf::radians(std::atan2(dir.y, dir.x)));
	}
 }

 void Enemy::move(sf::Vector2f pos_shift)
 {
	body.move(pos_shift);
 }