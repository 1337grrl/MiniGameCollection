#pragma once

#include <SFML/Graphics.hpp>

class Background {
public: 
	sf::Sprite background;
	sf::Sprite ground;

	Background();

	void init();
	void update(const float delta);
	void render();

private:
	const float scaleWidth = 2.5f;
	const float scaleHeight = 2.5f;
	const sf::Vector2f SCALE = sf::Vector2f(scaleWidth, scaleHeight);

	const int BACKGROUND_SPEED = 100;
	const int BACKGROUND_WIDTH = 1032;

	const int GROUND_SPEED = 150;
};