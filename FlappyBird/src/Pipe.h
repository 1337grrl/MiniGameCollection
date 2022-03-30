#pragma once

#include <SFML/Graphics.hpp>

class Pipe {
public:
	sf::Sprite pipe;

	Pipe();
	~Pipe();

	void init(const sf::Texture& t, float scaleWidth, float scaleHeight, const sf::Vector2f& p);
};