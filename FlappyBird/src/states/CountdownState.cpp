#include "CountdownState.h"
#include "../StateMachine.h"

void CountdownState::init() {
}

void CountdownState::handleInput() {

}

void CountdownState::update() {
	if (resetNeeded) {
		reset();
		resetNeeded = false;
	}
	float seconds = countdownClock.getElapsedTime().asSeconds();
	counter -= seconds;
	countdownClock.restart();
	if (counter <= 1.f) {
		gStateMachine.setState(StateMachine::StateNames::play);
		resetNeeded = true;
	}
}

void CountdownState::render() {
	displayCounter();
}

void CountdownState::displayCounter() {
	sf::Text msg;

	msg.setString(std::to_string(int(counter)));
	msg.setFont(gStateMachine.textures.font);
	msg.setCharacterSize(500);
	msg.setOrigin(msg.getLocalBounds().width * .5f, msg.getLocalBounds().height * .5f);
	msg.setPosition(WINDOW_CENTER);
	msg.move(0.f, -100.f);

	gWindow.draw(msg);
}

void CountdownState::reset() {
	countdownClock.restart();
	counter = 6.0f;
}