#include "Pipe.h"

Pipe::Pipe() {}
Pipe::~Pipe() {
	delete &pipe;
}

void Pipe::init(const sf::Texture& t, float scaleWidth, float scaleHeight, const sf::Vector2f& p) {
	pipe.setTexture(t);
	pipe.setScale(sf::Vector2f(scaleWidth, scaleHeight));
	pipe.setPosition(p);
}