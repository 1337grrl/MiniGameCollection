#pragma once

#include "State.h"


class CountdownState : public State {
public:
	virtual void init();
	virtual void handleInput();
	virtual void update();
	virtual void render();


private: 
	sf::Clock countdownClock;
	float counter;
	bool resetNeeded = true;

	void reset();
	void displayCounter();
};