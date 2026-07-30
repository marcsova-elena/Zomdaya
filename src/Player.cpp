 #include "Player.h"
 #include "configuration.hpp"
 #include <math.h>

 Player::Player()
 {
	body.setOrigin({radius / 2, radius / 2});
	body.setRadius(25);
	body.setPosition({conf::window_size_f.x / 2, conf::window_size_f.y / 2});
	body.setFillColor(sf::Color::Blue);
 }

 void Player::draw(sf::RenderWindow* window)
 {
	window->draw(body);
 }

 void Player::update(float dt, sf::RenderWindow* window)
 {
	// Keyboard movement - TODO acceleration and diagonal speed
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		move({0, -speed * dt});
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		move({0, speed * dt});
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		move({-speed * dt, 0});
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		move({speed * dt, 0});
	}

	// Mouse movement
	sf::Vector2i locMousePos = sf::Mouse::getPosition(*window);	// local mouse position
	rotation = sf::radians(std::atan2(locMousePos.y - body.getPosition().y, locMousePos.x - body.getPosition().x));
	body.setRotation(rotation);

 }

 void Player::move(sf::Vector2f pos_shift)
 {
	body.move(pos_shift);
 }