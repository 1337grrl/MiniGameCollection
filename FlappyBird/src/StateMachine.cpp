#include "StateMachine.h"


void StateMachine::init() {
	registerState(StateNames::start, new StartState());
	registerState(StateNames::countdown, new CountdownState());
	registerState(StateNames::play, new PlayState());	
	setState(StateNames::start);

	std::srand(time(NULL));
}

void StateMachine::handleInput() {
	state->handleInput();
}

void StateMachine::update() {
	shouldWindowClose();
	if (nextState != StateNames::count) {
		setState(nextState);
		nextState = StateNames::count;
	}
	getDelta();
	gBackground.update((const float) delta);
	state->update();
}

void StateMachine::render() {
	gWindow.clear(sf::Color::Black);
	gBackground.render();
	state->render();
	gWindow.display();
}

void StateMachine::getDelta() {
	delta = deltaClock.getElapsedTime().asSeconds();
	deltaClock.restart();
}

void StateMachine::registerState(StateNames sn, State* s)
{
	states.insert(std::pair<StateNames, State*>(sn, s));
	states.at(sn)->init();
}

void StateMachine::setState(StateNames sn) {
	auto it = states.find(sn);
	if (it != states.end()) {
		state = it->second;
	}
}

void StateMachine::shouldWindowClose() {
	{
		sf::Event e;

		while (gWindow.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				gWindow.close();
			}
		}
	}
}