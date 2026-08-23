#pragma once

#include <SFML/Graphics.hpp>

class Box
{
 public:
    sf::Vector2f size;
    sf::RectangleShape body;
    float health = 250;
    bool isAlive = true;
    Box(sf::Vector2f pos, sf::Vector2f size={50, 50}, sf::Angle angle=sf::radians(0));
    void draw(sf::RenderWindow *window);
};