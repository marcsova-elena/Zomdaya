#include "World.h"
#include <algorithm>

World::World()
{
	background.setFillColor(background_color);

	player = new Player();

	Enemy* enemy = new Enemy();
	enemies.push_back(enemy);
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
}

void World::update(float dt, sf::RenderWindow *window)
{
	player->update(dt, window);

	for(auto enemy : enemies)
	{
		enemy->update(dt, player->body.getPosition());
	}
	for(auto bullet : player->bullets)
	{
		if(!bullet->isAlive) continue;
		
		bullet->update(dt);
		
		if(isCircleOutOfBounds(bullet->body, border))
		{
			bullet->isAlive = false;
			continue;
		}
		for(auto enemy : enemies)
		{
			if(!enemy->isAlive) continue;
			
			// Enemy was shot
			if(circle_collision(bullet->body, enemy->body))
			{
				enemy->damage(bullet->damage);
				bullet->isAlive = false;
				break;	//stop checking this bullet on other enemies
			}
		}
	}

	// Player walls collision
	player->body.move(get_circleBorder_collision_vector(player->body, border));

	center_camera();

	// 3. Cleanup phase (free memory and shrink vectors)
    std::erase_if(enemies, [](Enemy* enemy) {
        if (!enemy || !enemy->isAlive) {
            delete enemy;
            return true;
        }
        return false;
    });

    std::erase_if(player->bullets, [](Bullet* bullet) {
        if (!bullet || !bullet->isAlive) {
            delete bullet;
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
}