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

	void init();
};