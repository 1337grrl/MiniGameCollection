#pragma once

#include "State.h"
#include "../PipePair.h"
#include <deque>
#include <time.h>


class PlayState : public State {
public:
	std::deque<PipePair> pairs;
	int frameCounter = 0;
	
	virtual void init();
	virtual void handleInput();
	virtual void update();
	virtual void render();

private:
	bool collisionDetected = false;
	void reset();
};