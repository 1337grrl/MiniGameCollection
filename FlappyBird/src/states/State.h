#pragma once

#include <SFML/Graphics.hpp>

class State {
public:
	virtual void init() = 0;
	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

};
