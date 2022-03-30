#pragma once

#include <SFML/Graphics.hpp>
#include "TexturePack.h"

class Bird {
public:
	sf::Sprite bird;


	Bird();
	~Bird();

	void init(sf::Texture t, sf::Vector2f p, float scaleWidth, float scaleHeight);

	void update(float delta);

	void render();

private:
	inline sf::Vector2f getPosition() { return bird.getPosition(); }
};
