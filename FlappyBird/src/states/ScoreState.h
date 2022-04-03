#pragma once

#include "State.h"


class ScoreState : public State {
public:
	virtual void init();
	virtual void handleInput();
	virtual void update();
	virtual void render();

private:
	sf::Text scoreMsg;
	bool scoreMsgInitialised = false;
	void initScoreMsg();
};