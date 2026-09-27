#include "collisions.h"
#include <math.h>
#include <algorithm>

// Doesn't currently expect a different left corner position than {0, 0} or border transformation
bool isOutOfBounds(const sf::CircleShape &circle, const sf::FloatRect &border)
{
	if(circle.getPosition().x >= border.size.x + circle.getRadius() || circle.getPosition().y >= border.size.y + circle.getRadius()
			|| circle.getPosition().x <= -circle.getRadius() || circle.getPosition().y <= -circle.getRadius())
			return true;
	return false;
}

// Basic collision check between two circles
bool areColiding(const sf::CircleShape &obj1, const sf::CircleShape &obj2)
{
	float radiusSquared = (obj1.getRadius() + obj2.getRadius()) * (obj1.getRadius() + obj2.getRadius());
	if((obj1.getPosition() - obj2.getPosition()).lengthSquared() <= radiusSquared)
		return true;
	return false;
}

// Returns a minimum translation vector for a circle and a non rotated rectangle collision
sf::Vector2f circleBoxCollision(const sf::CircleShape &circle, const sf::RectangleShape &rect)
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

// Returns a minimum translation vector for a circle and a non rotated rectangle border
sf::Vector2f circleBorderCollision(const sf::CircleShape &circle, const sf::FloatRect &border)
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

std::pair<sf::Vector2f, sf::Vector2f> circleCircleCollision(const sf::CircleShape &circle1, const sf::CircleShape &circle2, float mass1, float mass2)
{
	float radiuses = circle1.getRadius() + circle2.getRadius();
	sf::Vector2f diff = circle1.getPosition() - circle2.getPosition();
	float distSq = diff.lengthSquared();
	// Check if collision has occurred
	if(distSq <= (radiuses * radiuses) && distSq > 0.0001f)
	{
		float dist = std::sqrt(distSq);
		sf::Vector2f normal = diff / dist;
		float overlap = radiuses - dist;

		float ratio1 = mass2 / (mass1 + mass2);
		float ratio2 = mass1 / (mass1 + mass2);
		sf::Vector2f push1 = normal * (overlap * ratio1);
		sf::Vector2f push2 = -normal * (overlap * ratio2);
		return {push1, push2}; 
	}
	return {{0.f, 0.f}, {0.f, 0.f}};	// no collision
}

/*
	SAT Collision functions
*/

inline float dotProduct(const sf::Vector2f &a, const sf::Vector2f &b)
{
	return (a.x * b.x) + (a.y * b.y);
}

std::vector<sf::Vector2f> getVertices(const sf::RectangleShape &shape)
{
	std::vector<sf::Vector2f> verts;
	verts.reserve(4);
	sf::Transform t = shape.getTransform();
	for(std::size_t i = 0;i < 4; i++)
		verts.push_back(t.transformPoint(shape.getPoint(i)));
	return verts;
}

std::pair<float, float> project(const sf::Vector2f &axis, const std::vector<sf::Vector2f> &verts)
{
	float pMin = std::numeric_limits<float>::infinity();
	float pMax = -std::numeric_limits<float>::infinity();
	for(const auto& point : verts)
	{
		float p = dotProduct(point, axis);
		pMin = std::min(p, pMin);
		pMax = std::max(p, pMax);
	}
	return {pMin, pMax};
}

std::pair<float, float> project(const sf::Vector2f &axis, const sf::CircleShape &circle)
{
	float p = dotProduct(circle.getPosition(), axis);
	return {p - circle.getRadius(), p + circle.getRadius()};
}

sf::Vector2f closest_vert(const std::vector<sf::Vector2f> &rect_verts, const sf::Vector2f &circle_center)
{
	sf::Vector2f closest;
	float max_dist_sq = std::numeric_limits<float>::infinity();
	float dist;
	for(const auto &vert : rect_verts)
	{
		if((dist = (circle_center - vert).lengthSquared()) < max_dist_sq)
		{
			max_dist_sq = dist;
			closest = vert;
		}
	}
	return closest;
}

// Generic tester - accepts any projection lambda for shape A and shape B
template <typename ProjA, typename ProjB>
CollisionResult SAT(const std::vector<sf::Vector2f> &axes, 
					const sf::Vector2f &centerA, const sf::Vector2f &centerB,
					ProjA&& projectA, ProjB&& projectB)
{
	CollisionResult result;

	// We track the minimum overlap and the axis for mtv vector
	float minOverlap = std::numeric_limits<float>::infinity();
	sf::Vector2f pushAxis;
	for(const auto &axis : axes)
	{
		auto [minA, maxA] = projectA(axis);
		auto [minB, maxB] = projectB(axis);

		if(maxA < minB || maxB < minA)	// gap exist, objects cannot collide
		{
			result.collided = false;
			result.mtv = {0.f, 0.f};
			return result;
		}

		// Calculate 1D overlap length
		float overlap = std::min(maxA, maxB) - std::max(minA, minB);
		if(overlap < minOverlap)
		{
			minOverlap = overlap;
			pushAxis = axis;
		}
	}
	result.collided = true;
	
	// Ensure push direction from A to B
	if(dotProduct((centerB - centerA), pushAxis) < 0.f)
		pushAxis = -pushAxis;

	result.mtv = pushAxis * minOverlap;
	return result;
}

CollisionResult checkSATCollision(sf::RectangleShape &a, sf::RectangleShape &b)
{
	std::vector<sf::Vector2f> a_verts = getVertices(a);
	std::vector<sf::Vector2f> b_verts = getVertices(b);

	std::vector<sf::Vector2f> axes;
	axes.reserve(4);

	// We can skip parallel axis, so we need to check just 2 per rectangle
	axes.push_back((a_verts[0] - a_verts[1]).perpendicular().normalized());
	axes.push_back((a_verts[1] - a_verts[2]).perpendicular().normalized());

	axes.push_back((b_verts[0] - b_verts[1]).perpendicular().normalized());
	axes.push_back((b_verts[1] - b_verts[2]).perpendicular().normalized());

	return SAT(axes, a.getPosition(), b.getPosition(),
			[&](const sf::Vector2f& axis) { return project(axis, a_verts); },
			[&](const sf::Vector2f& axis) { return project(axis, b_verts); });
}

CollisionResult checkSATCollision(sf::CircleShape &circle, sf::RectangleShape &rect)
{
	std::vector<sf::Vector2f> rect_verts = getVertices(rect);
	std::vector<sf::Vector2f> axes;
	axes.reserve(3);

	// Two axes from the rectangle, two perpendicular sides
	axes.push_back((rect_verts[0] - rect_verts[1]).perpendicular().normalized());
	axes.push_back((rect_verts[1] - rect_verts[2]).perpendicular().normalized());

	axes.push_back((closest_vert(rect_verts, circle.getPosition()) - circle.getPosition()).normalized());

	return SAT(axes, rect.getPosition(), circle.getPosition(),
			[&](const sf::Vector2f& axis) { return project(axis, circle); },
			[&](const sf::Vector2f& axis) { return project(axis, rect_verts); });
}
