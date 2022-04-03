#include "ScoreState.h"
#include "../StateMachine.h"

void ScoreState::init() {	
}

void ScoreState::handleInput() {
	if (resetEnabled && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		gStateMachine.setState(StateMachine::StateNames::countdown);
		scoreMsgInitialised = false;
		frameCounter = 0;
		resetEnabled = false;
	}
}

void ScoreState::update() {	
	frameCounter++;
	if (frameCounter >= 60) {
		resetEnabled = true;
	}
	if (!scoreMsgInitialised) {
		initScoreMsg();
		scoreMsgInitialised = true;
	}
}

void ScoreState::render() {
	gBird.render();
	gWindow.draw(scoreMsg);
}

void ScoreState::initScoreMsg() {
	sf::Text msg;

	std::string message = "GAME OVER!\nSCORE: ";
	message += std::to_string(gScore);
	msg.setString(message);
	msg.setFont(gTextures.font);
	msg.setCharacterSize(150);
	msg.setOrigin(msg.getLocalBounds().width * .5f, msg.getLocalBounds().height * .5f);
	msg.setPosition(WINDOW_CENTER);

	scoreMsg = msg;
}