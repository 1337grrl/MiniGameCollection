#pragma once

#include "State.h"


class PlayState : public State {
public:
	virtual void enter();
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void exit();
};