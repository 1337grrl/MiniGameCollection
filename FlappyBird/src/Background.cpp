#include "Background.h"
#include "StateMachine.h"


void Background::init() {
	background.setTexture(gTextures.background);
	background.setScale(gTextures.SCALE);
	ground.setTexture(gTextures.ground);
	GROUND_POSITION_Y = 720.f - ground.getLocalBounds().height * gTextures.scaleHeight;
	ground.setPosition(sf::Vector2f(0.f, GROUND_POSITION_Y));
	ground.setScale(gTextures.SCALE);
}


void Background::update(const float delta) {
	const int WINDOW_WIDTH = 1280;

	sf::Vector2f backgroundScroll, groundScroll;
	backgroundScroll = sf::Vector2f(-(int(BACKGROUND_SPEED * delta) % BACKGROUND_WIDTH), 0.f);
	groundScroll = sf::Vector2f(-(int(GROUND_SPEED * delta) % WINDOW_WIDTH), 0.f);

	if (background.getPosition().x <= -BACKGROUND_WIDTH) {
		background.setPosition(sf::Vector2f(0.f, 0.f));
	}
	else {
		background.move(backgroundScroll);
	}
	if (ground.getPosition().x <= -WINDOW_WIDTH) {
		ground.setPosition(sf::Vector2f(0.f, GROUND_POSITION_Y));
	}
	else {
		ground.move(groundScroll);
	}
}

void Background::render() {
	gWindow.draw(background);
	gWindow.draw(ground);
}