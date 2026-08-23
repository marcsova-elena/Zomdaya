#include "Box.h"

Box::Box(sf::Vector2f pos, sf::Vector2f size, sf::Angle angle)
{
    body.setOrigin({size.x / 2, size.y / 2});
    body.setSize(size);
    
    body.setFillColor(sf::Color(63, 40, 4));
    body.setOutlineColor(sf::Color::Black);
    body.setOutlineThickness(2);
    
    body.setPosition(pos);
    body.setRotation(angle);
}

void Box::draw(sf::RenderWindow *window)
{ 
	window->draw(body);
}