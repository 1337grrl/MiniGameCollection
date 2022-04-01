#include "StateMachine.h"


void StateMachine::init(sf::RenderWindow* w) {
	window = w;	
	textures.init();
	registerState(StateNames::start, new StartState());
	registerState(StateNames::countdown, new CountdownState());
	//registerState(StateNames::countdown, state);
	//registerState(StateNames::play, state);	
	setState(StateNames::start);
	background.init(&textures.background, &textures.ground);
}

void StateMachine::handleInput() {
	state->handleInput();
}

void StateMachine::update() {
	shouldWindowClose(window);
	if (nextState != StateNames::count) {
		setState(nextState);
		nextState = StateNames::count;
	}
	getDelta();
	background.update((const float) delta);
	state->update();
}

void StateMachine::render() {
	window->clear(sf::Color::Black);
	background.render(window);
	state->render();
	window->display();
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

void StateMachine::shouldWindowClose(sf::RenderWindow* w) {
	{
		sf::Event e;

		while (w->pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				w->close();
			}
		}
	}
}