#pragma once

#include <SFML/Graphics.hpp>

class State {
public:

	virtual void init() = 0;
	virtual void handleInput() = 0;
	virtual void update(sf::RenderWindow* w, const sf::Font* f) = 0;
	virtual void render(sf::RenderWindow* w, const sf::Font* f) = 0;

	void shouldWindowClose(sf::RenderWindow* w);
};
