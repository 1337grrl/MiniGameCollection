#include "Bird.h"

Bird::Bird() {}
Bird::~Bird() {
	delete& bird;
}

void Bird::init(sf::Texture t, sf::Vector2f p, float scaleWidth, float scaleHeight) {
	bird.setTexture(t);
	bird.setScale(sf::Vector2f(scaleWidth, scaleHeight));
	bird.setOrigin(bird.getLocalBounds().width * .5, bird.getLocalBounds().height * .5f);
	bird.setPosition(p);
}

void Bird::update(float delta) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		bird.move(ANTI_GRAVITY);
	}
	bird.move(GRAVITY * delta);
}

void Bird::render() {

}