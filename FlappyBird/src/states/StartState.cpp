#include "StartState.h"
#include "../StateMachine.h"


void StartState::init() {
	initStartMsg();
}

void StartState::update() {
}

void StartState::handleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		gStateMachine.setState(StateMachine::StateNames::countdown);
	}
}

void StartState::render() {
	displayStart();
}

void StartState::initStartMsg() {
	sf::Text msg;

	msg.setString("Press Space \nto start");
	msg.setFont(gTextures.font);
	msg.setCharacterSize(150);
	msg.setOrigin(msg.getLocalBounds().width * .5f, msg.getLocalBounds().height * .5f);
	msg.setPosition(WINDOW_CENTER);

	startMsg = msg;
}

void StartState::displayStart() {

	gWindow.draw(startMsg);

}

