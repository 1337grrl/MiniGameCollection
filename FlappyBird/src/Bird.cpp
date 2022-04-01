#include "Bird.h"
#include "StateMachine.h"

Bird::Bird() : score { 0 } {}
Bird::~Bird() {
	delete& bird;
}

void Bird::init(sf::Vector2f p, float scaleWidth, float scaleHeight) {
	bird.setTexture(gTextures.bird);
	bird.setScale(sf::Vector2f(scaleWidth, scaleHeight));
	bird.setOrigin(bird.getLocalBounds().width * .5, bird.getLocalBounds().height * .5f);
	bird.setPosition(p);

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