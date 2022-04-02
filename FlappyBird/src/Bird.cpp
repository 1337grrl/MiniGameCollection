#include "Bird.h"
#include "StateMachine.h"

Bird::Bird() : score { 0 } {}


void Bird::init() {
	bird.setTexture(gTextures.bird);
	bird.setScale(gTextures.SCALE);
	bird.setOrigin(bird.getLocalBounds().width * .5f, bird.getLocalBounds().height * .5f);
	bird.setPosition(WINDOW_CENTER);

	score = 0;
}

void Bird::update(float delta) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		bird.move(ANTI_GRAVITY);
	}
	bird.move(GRAVITY * delta);
}

void Bird::render() {
	gWindow.draw(bird);
}