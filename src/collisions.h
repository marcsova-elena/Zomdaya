#pragma once

#include <SFML/Graphics.hpp>

bool isCircleOutOfBounds(const sf::CircleShape &circle, const sf::FloatRect &border);
bool circle_collision(const sf::CircleShape &obj1, const sf::CircleShape &obj2);
bool isCircleOutOfBounds(const sf::CircleShape &circle, const sf::FloatRect &border);
sf::Vector2f get_circleBox_collision_vector(const sf::CircleShape &circle, const sf::RectangleShape &rect);
sf::Vector2f get_circleBorder_collision_vector(const sf::CircleShape &circle, const sf::FloatRect &border);
std::pair<sf::Vector2f, sf::Vector2f> get_circleCircle_collision_vectors(const sf::CircleShape &circle, const sf::CircleShape &circle2, float mass1=50, float mass2=50);