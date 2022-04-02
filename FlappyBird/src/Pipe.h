#pragma once

#include <SFML/Graphics.hpp>

class Pipe {
public:
	sf::Sprite pipe;


	void init(sf::Vector2f& p);
	void move(float x);
	void draw();
};