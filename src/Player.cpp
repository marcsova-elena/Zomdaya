 #include "Player.h"
 #include "configuration.hpp"

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
 void Player::update(float dt)
 {

 }