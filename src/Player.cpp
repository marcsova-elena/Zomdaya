#include "Player.h"
#include "configuration.hpp"
#include <math.h>

Player::Player()
{
	body.setOrigin({radius, radius});
	body.setRadius(radius);
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

	// Shooting timer increase
	gun.shootTimer += dt;

	// Mouse movement
	sf::Vector2i locMousePos = sf::Mouse::getPosition(*window);	// local mouse position
	sf::Vector2f worldMousePos = window->mapPixelToCoords(locMousePos);
	sf::Vector2f delta = worldMousePos - body.getPosition();
	if(delta.lengthSquared() < 0.001f) return;
	body.setRotation(delta.angle());

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		leftClickPressed = true;
		gun.shoot(&bullets, body.getPosition(), delta.normalized());
	}
	else if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		leftClickPressed = false;
}

void Player::move(sf::Vector2f pos_shift)
{
	body.move(pos_shift);
}

Player::~Player()
{
	for(auto bullet : bullets)
		delete bullet;
}