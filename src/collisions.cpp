#include "collisions.h"
#include <math.h>
#include <algorithm>

// Doesn't currently count with different left corner position than {0, 0}
bool isCircleOutOfBounds(const sf::CircleShape &circle, const sf::FloatRect &border)
{
	if(circle.getPosition().x >= border.size.x + circle.getRadius() || circle.getPosition().y >= border.size.y + circle.getRadius()
			|| circle.getPosition().x <= -circle.getRadius() || circle.getPosition().y <= -circle.getRadius())
			return true;
	return false;
}

bool circle_collision(const sf::CircleShape &obj1, const sf::CircleShape &obj2)
{
	float radiusSquared = (obj1.getRadius() + obj2.getRadius()) * (obj1.getRadius() + obj2.getRadius());
	if((obj1.getPosition() - obj2.getPosition()).lengthSquared() <= radiusSquared)
		return true;
	return false;
}

sf::Vector2f get_circleBox_collision_vector(const sf::CircleShape &circle, const sf::RectangleShape &rect)
{
	sf::Vector2f closest;
	float radius = circle.getRadius();
	sf::FloatRect bounds = rect.getGlobalBounds();
	closest.x = std::clamp(circle.getPosition().x, bounds.position.x, bounds.position.x + bounds.size.x);
	closest.y = std::clamp(circle.getPosition().y, bounds.position.y, bounds.position.y + bounds.size.y);

	sf::Vector2f diff = circle.getPosition() - closest;
	float distSq = diff.lengthSquared();

	if((distSq <= (radius * radius)) && distSq > 0.0001f)
	{
		float dist = std::sqrt(distSq);
		float overlap = radius - dist;
		
		sf::Vector2f normal = diff / dist;
		return normal * overlap;
	}
	return {0, 0}; // no collision
}

sf::Vector2f get_circleBorder_collision_vector(const sf::CircleShape &circle, const sf::FloatRect &border)
{
	float radius = circle.getRadius();
    sf::Vector2f pos = circle.getPosition();
    sf::Vector2f pushBack{0.0f, 0.0f};

    // Calculate boundary limits based on the border rect's position & size
    float leftBound   = border.position.x + radius;
    float rightBound  = border.position.x + border.size.x - radius;
    float topBound    = border.position.y + radius;
    float bottomBound = border.position.y + border.size.y - radius;

    // Left boundary
    if (pos.x < leftBound)
        pushBack.x = leftBound - pos.x;
		
    // Right boundary
    else if (pos.x > rightBound)
        pushBack.x = rightBound - pos.x;

    // Top boundary
    if (pos.y < topBound)
        pushBack.y = topBound - pos.y;

    // Bottom boundary
    else if (pos.y > bottomBound)
        pushBack.y = bottomBound - pos.y;

    return pushBack;
}

sf::Vector2f get_circleCircle_collision_vector(const sf::CircleShape &circle1, const sf::CircleShape &circle2)
{

}