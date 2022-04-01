#pragma once

#include "State.h"

class StartState : public State {
public:

	virtual void init();
	virtual void handleInput();
	virtual void update();
	virtual void render();

private:
	sf::Text startMsg;
	void initStartMsg();
	void displayStart();
};