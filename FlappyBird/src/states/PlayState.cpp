#include "PlayState.h"
#include "../StateMachine.h"

void PlayState::init() {
}

void PlayState::handleInput() {

}

void PlayState::update() {

	// Pipe spawning

	// Pipe moving

	// Bird moving
	gBird.update(gStateMachine.delta);

	// collision detection

	// Update score
}

void PlayState::render() {
	// Draw Pipes

	// Draw bird
	gBird.render();
	//Draw score

}
