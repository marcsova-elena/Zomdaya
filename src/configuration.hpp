#pragma once

namespace conf
{
	//Window configuration
	const sf::Vector2u window_size = {800u, 600u};
	const sf::Vector2f window_size_f = static_cast<sf::Vector2f>(window_size);
	uint32_t max_framerate = 144;
	const float dt = 1.0f / static_cast<float>(max_framerate);
}