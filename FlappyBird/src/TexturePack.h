#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class TexturePack {
public:
	sf::Texture bird;
	sf::Texture ground;
	sf::Texture background;
	sf::Texture pipe;
	sf::Font font;

	const float scaleWidth = 2.5f;
	const float scaleHeight = 2.5f;
	const sf::Vector2f SCALE = sf::Vector2f(scaleWidth, scaleHeight);

	void init();
};