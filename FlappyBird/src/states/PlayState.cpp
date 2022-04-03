#include "PlayState.h"
#include "../StateMachine.h"


void PlayState::init() {
}

void PlayState::handleInput() {

}

void PlayState::update() {
	if (collisionDetected) {
		reset();
	}

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
		if (!pairs.empty() && pairs.front().getPositionX() < -pairs[i].pipeWidth) {
			pairs.pop_front();
		}
	}

	// Bird moving
	gBird.update(gStateMachine.delta);

	// collision detection		

	for (size_t i = 0; i < pairs.size(); ++i) {
 		if (gBird.collisionDetected(pairs[i])) {
			collisionDetected = true;
 			gStateMachine.setState(StateMachine::StateNames::score);
		}
	} 
	// Update score
	updateScoreDisplay();
}

void PlayState::render() {
	// Draw Pipes
	for (PipePair p : pairs) {
		p.render();
	}

	// Draw bird
	gBird.render();
	//Draw score
	gWindow.draw(currentScore);

}

void PlayState::reset() {
	pairs.clear();
	collisionDetected = false;
	gScore = 0;
	gBird.bird.setPosition(WINDOW_CENTER);
}

void PlayState::updateScoreDisplay() {
	sf::Text msg;

	msg.setString(std::to_string(gScore));
	msg.setFont(gTextures.font);
	msg.setCharacterSize(150);
	msg.setPosition(50.f, 50.f);

	currentScore = msg;
}