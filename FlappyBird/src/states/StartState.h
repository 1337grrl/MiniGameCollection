#pragma once

#include "../Bird.h""
#include "State.h"

class StartState : public State {
public:

	virtual void init();
	virtual void update(sf::RenderWindow* w, const sf::Font* f);
	virtual void render(sf::RenderWindow* w, const sf::Font* f);

private:
	void displayStart(sf::RenderWindow* w, const sf::Font* f);
};