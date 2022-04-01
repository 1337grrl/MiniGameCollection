#pragma once

#include "State.h"


class PlayState : public State {
public:
	virtual void init();
	virtual void handleInput();
	virtual void update();
	virtual void render();
};