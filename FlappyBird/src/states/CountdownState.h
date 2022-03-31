#pragma once

#include "State.h"


class CountdownState : public State {
public:
	virtual void enter();
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void exit();
};