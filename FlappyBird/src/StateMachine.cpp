#include "StateMachine.h"


void StateMachine::init(sf::RenderWindow* w, State* s) {
	window = w;
	state = s;
	state->init();
	textures.init();
	background.init(&textures.background, &textures.ground);
}

void StateMachine::update() {
	getDelta();
	background.update((const float) delta);
	state->update(window, &textures.font);
}

void StateMachine::render() {
	window->clear(sf::Color::Black);
	background.render(window);
	state->render(window, &textures.font);
	window->display();
}

void StateMachine::getDelta() {
	delta = deltaClock.getElapsedTime().asSeconds();
	deltaClock.restart();
}