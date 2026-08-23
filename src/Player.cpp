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
	// Gather input direction
	sf::Vector2f inputDir = {0, 0};
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) inputDir.y -= 1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) inputDir.y += 1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) inputDir.x -= 1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) inputDir.x += 1;

	// Normalize directional vector
	if(inputDir.lengthSquared() > 0.f)
		inputDir = inputDir.normalized();

	sf::Vector2f targetVelocity = inputDir * speed;
	
	// Acceleration and deacceleration
	if(inputDir.lengthSquared() > 0.f)
		velocity += (targetVelocity - velocity) * acceleration * dt;
	else
		velocity -= velocity * friction * dt;

	move(velocity * dt);

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
	if(pos_shift.x == 0 && pos_shift.y == 0) return;
	body.move(pos_shift);
}

void Player::damage(float damage)
{
	health -= damage;
	if(health <= 0)
	{
		isAlive = false;
	}
}

Player::~Player()
{
	for(auto bullet : bullets)
		delete bullet;
}