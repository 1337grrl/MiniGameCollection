#pragma once

#include <SFML/Graphics.hpp>

class Background {
public: 
	sf::Sprite background;
	sf::Sprite ground;

	void init();
	void update(const float delta);
	void render();

private:
	const int BACKGROUND_SPEED = 100;
	const int BACKGROUND_WIDTH = 1032;

	float GROUND_POSITION_Y = 0.f;
	const int GROUND_SPEED = 150;
};