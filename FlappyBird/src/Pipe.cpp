#include "Pipe.h"
#include "StateMachine.h"


void Pipe::init(sf::Vector2f& p) {
	pipe.setTexture(gTextures.pipe);
	pipe.setScale(gTextures.SCALE);
	pipe.setPosition(p);
}

void Pipe::move(float x) {
	pipe.move(x, 0.f);
}

void Pipe::draw() {
	gWindow.draw(pipe);
}