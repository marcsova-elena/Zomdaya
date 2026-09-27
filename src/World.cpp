#include "World.h"
#include <algorithm>
#include <random>

#define ENEMY_NUM 5
#define BOX_NUM 5

namespace Random
{
	inline std::mt19937& getEngine()
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		return gen;
	}
	inline int getInt(int min, int max) 
	{
        std::uniform_int_distribution<int> dist(min, max);
        return dist(getEngine());
    }
    inline float getFloat(float min, float max) 
	{
        std::uniform_real_distribution<float> dist(min, max);
        return dist(getEngine());
    }
}

World::World()
{
	printf("Initializing world\n");
	background.setFillColor(background_color);

	player = new Player();

	for(int i = 0; i < ENEMY_NUM; i++)
	{
		Enemy* enemy = new Enemy({0, 0});
		float posX = Random::getFloat(enemy->body.getRadius(), mapSize.x - enemy->body.getRadius());
		float posY = Random::getFloat(enemy->body.getRadius(), mapSize.y - enemy->body.getRadius());
		enemy->body.setPosition({posX, posY});
		enemies.push_back(enemy);
	}

	for(int i = 0; i < BOX_NUM; i++)
	{
		float size_x = float(Random::getInt(70, 85));
		float size_y = float(Random::getInt(70, 85));
		float angle = float(Random::getInt(0, 180));
		Box* box = new Box({0, 0}, {size_x, size_y}, sf::Angle(sf::radians(angle)));

		float posX = Random::getFloat(box->body.getScale().x + 5, mapSize.x - box->body.getScale().x - 5);
		float posY = Random::getFloat(box->body.getScale().y + 5, mapSize.y - box->body.getScale().y - 5);
		box->body.setPosition({posX, posY});
		boxes.push_back(box);
	}

}

void World::draw(sf::RenderWindow *window)
{
	window->draw(background);
	player->draw(window);
	for(auto enemy : enemies)
	{
		enemy->draw(window);
	}
	for(auto bullet : player->bullets)
	{
		bullet->draw(window);
	}
	for(auto box : boxes)
	{
		box->draw(window);
	}
}

void World::update(float dt, sf::RenderWindow *window)
{
	// Update player based off of player's input
	player->update(dt, window);

	/*
		Collisions
	*/
	// Update enemies and their collisions with player
	for(auto enemy : enemies)
	{
		enemy->update(dt, player->body.getPosition());
		std::pair<sf::Vector2f, sf::Vector2f> pushVecs = circleCircleCollision(player->body, enemy->body, player->mass, enemy->mass);
		player->move(pushVecs.first);
		enemy->move(pushVecs.second);
	}

	// ssize for signed integer, otherwise would underflow
	for(auto i = 0; i < std::ssize(enemies) - 1; i++)
	{
		for(auto j = i + 1; j < enemies.size(); j++)
		{
			std::pair<sf::Vector2f, sf::Vector2f> pushVecs = circleCircleCollision(enemies[i]->body, enemies[j]->body, enemies[i]->mass, enemies[j]->mass);
			enemies[i]->move(pushVecs.first);
			enemies[j]->move(pushVecs.second);
		}
	}

	for(auto bullet : player->bullets)
	{
		if(!bullet->isAlive) continue;
		
		bullet->update(dt);
		
		if(isOutOfBounds(bullet->body, border))
		{
			bullet->isAlive = false;
			continue;
		}
		for(auto enemy : enemies)
		{
			if(!enemy->isAlive) continue;
			
			// Enemy was shot
			if(areColiding(bullet->body, enemy->body))
			{
				enemy->damage(bullet->damage);
				bullet->isAlive = false;
				break;	//stop checking this bullet on other enemies
			}
		}
	}

	// Enemies x boxes collision
	for(auto enemy : enemies)
	{
		for(auto box : boxes)
		{
			CollisionResult col = checkSATCollision(enemy->body, box->body);
			if(col.collided)
			{
				enemy->move(col.mtv);
			}
		}
	}

	// Player x walls collision
	player->body.move(circleBorderCollision(player->body, border));	

	//Player x boxes collision
	for(auto box : boxes)
	{
		CollisionResult col = checkSATCollision(player->body, box->body);
		if(col.collided)
		{
			player->move(col.mtv);
		}
	}

	// Update camera on player
	center_camera();

	// Cleanup (free memory and shrink vectors)
    std::erase_if(enemies, [](Enemy* enemy) 
	{
        if (!enemy || !enemy->isAlive) 
		{
            delete enemy;
            return true;
        }
        return false;
    });

    std::erase_if(player->bullets, [](Bullet* bullet) 
	{
        if (!bullet || !bullet->isAlive) 
		{
            delete bullet;
            return true;
        }
        return false;
    });
	std::erase_if(boxes, [](Box* box) 
	{
        if (!box || !box->isAlive) 
		{
            delete box;
            return true;
        }
        return false;
    });
}

// Clamps and centers the camera
void World::center_camera()
{
	sf::Vector2f playerPos = player->body.getPosition();
	sf::Vector2f viewSize = camera.getSize();

	// Calculate the camera's min and max allowed center positions
    float minX = viewSize.x / 2.0f;
    float maxX = mapSize.x - (viewSize.x / 2.0f);

    float minY = viewSize.y / 2.0f;
    float maxY = mapSize.y - (viewSize.y / 2.0f);

	// 1. If the map is LARGER than the view, clamp normally
    sf::Vector2f clampedCenter;
    
    if(mapSize.x >= viewSize.x)
        clampedCenter.x = std::clamp(playerPos.x, minX, maxX);
    else // Map is smaller than window width: center on map
        clampedCenter.x = mapSize.x / 2.0f; 

    if(mapSize.y >= viewSize.y) 
        clampedCenter.y = std::clamp(playerPos.y, minY, maxY);
    else // Map is smaller than window height: center on map
        clampedCenter.y = mapSize.y / 2.0f;

    camera.setCenter(clampedCenter);
}

World::~World()
{
	// Cleanup
	delete player;
	for(int i = 0; i < sizeof(enemies); i++)
		delete enemies[i];
	for(int i = 0; i < sizeof(boxes); i++)
		delete boxes[i];
}