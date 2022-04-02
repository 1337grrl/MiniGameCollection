#pragma once

#include <SFML/Graphics.hpp>
#include "TexturePack.h"

class Bird {
public:
	sf::Sprite bird;
	uint16_t score;

	Bird();

	void init();

	void update(float delta);

	void render();

private:
	inline sf::Vector2f getPosition() { return bird.getPosition(); }

	const sf::Vector2f GRAVITY = sf::Vector2f(0.f, 250.f);
	const sf::Vector2f ANTI_GRAVITY = sf::Vector2f(0.f, -15.f);
};
