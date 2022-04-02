#include "PlayState.h"
#include "../StateMachine.h"

void PlayState::init() {
}

void PlayState::handleInput() {

}

void PlayState::update() {

	// Pipe spawning
	if (frameCounter % 60 == 0) {
 		PipePair pair;
		pair.spawn();
		pairs.push_back(pair);
		frameCounter = 0;
	}
	frameCounter++;

	// Pipe moving
	for (size_t i = 0; i < pairs.size(); ++i) {
 		pairs[i].update();
		if (!pairs.empty() && pairs.front().getPositionX() < - pairs[i].pipeWidth * 2.f) {
			pairs.pop_front();
		}
	}
	// Bird moving
	gBird.update(gStateMachine.delta);

	// collision detection

	// Update score
}

void PlayState::render() {
	// Draw Pipes
	for (PipePair p : pairs) {
		p.render();
	}

	// Draw bird
	gBird.render();
	//Draw score

}
