#pragma once

#include <SFML/Graphics.hpp>

bool isOutOfBounds(const sf::CircleShape &circle, const sf::FloatRect &border);
bool areColiding(const sf::CircleShape &obj1, const sf::CircleShape &obj2);
sf::Vector2f circleBoxCollision(const sf::CircleShape &circle, const sf::RectangleShape &rect);
sf::Vector2f circleBorderCollision(const sf::CircleShape &circle, const sf::FloatRect &border);
std::pair<sf::Vector2f, sf::Vector2f> circleCircleCollision(const sf::CircleShape &circle1, const sf::CircleShape &circle2, float mass1=50, float mass2=50);

// Separating Axis Theorem functions & objects
struct CollisionResult
{
	bool collided = false;
	sf::Vector2f mtv;
};
inline float dotProduct(const sf::Vector2f &a, const sf::Vector2f &b);
std::vector<sf::Vector2f> getVertices(const sf::RectangleShape &shape);
std::pair<float, float> project(const sf::Vector2f &axis, const std::vector<sf::Vector2f> &verts);
std::pair<float, float> project(const sf::Vector2f &axis, const sf::CircleShape &circle);
sf::Vector2f closest_vert(const std::vector<sf::Vector2f> &rect_verts, const sf::Vector2f &circle_pos);
template <typename ProjA, typename ProjB> CollisionResult SAT(const std::vector<sf::Vector2f> &axes, 
					const sf::Vector2f &centerA, const sf::Vector2f &centerB,
					ProjA&& projectA, ProjB&& projectB);
CollisionResult checkSATCollision(sf::RectangleShape &a, sf::RectangleShape &b);
CollisionResult checkSATCollision(sf::CircleShape &circle, sf::RectangleShape &rect);
