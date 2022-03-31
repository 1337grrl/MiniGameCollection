#include "StartState.h"
#include "State.h"

void StartState::init() {}
void StartState::update(sf::RenderWindow* w, const sf::Font* f) {
	shouldWindowClose(w);
	
}
void StartState::render(sf::RenderWindow* w, const sf::Font* f) {
	displayStart(w, f);
}

void StartState::displayStart(sf::RenderWindow* w, const sf::Font* f) {
	sf::Text msg;

	msg.setString("Press Space \nto start");
	msg.setFont(*f);
	msg.setCharacterSize(150);
	msg.setOrigin(msg.getLocalBounds().width * .5f, msg.getLocalBounds().height * .5f);
	msg.setPosition(sf::Vector2f(w->getSize())*.5f);

	w->draw(msg);
}