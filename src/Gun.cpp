#include "Gun.h"

Gun::Gun()
{

}

Gun::~Gun()
{

}

void Gun::shoot(std::vector<Bullet*> *bullets, sf::Vector2f pos, sf::Vector2f dir)
{
	if(shootTimer < fireSpeed) return; //TODO: add like a sound or something
	Bullet* bullet = new Bullet(pos, dir, damage);
	bullets->push_back(bullet);
	shootTimer = 0.f;
}