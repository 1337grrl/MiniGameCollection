#include "PipePair.h"

PipePair::PipePair() {}
PipePair::~PipePair() {
	delete& lowerPipe;
	delete& upperPipe;
}

void PipePair::init(const sf::Texture& t, float scaleWidth, float scaleHeight, const sf::Vector2f& p, float pG) {
	lowerPipe.init(t, scaleWidth, scaleHeight, p);
	upperPipe.init(t, scaleWidth, scaleHeight, p);
	rotate(upperPipe);

	pipeWidth = t.getSize().x * scaleWidth;
	pipeGap = pG;
}
void PipePair::update(float delta) {}

void PipePair::render() {}

void PipePair::rotate(Pipe& p) {
	p.pipe.setRotation(180);
	p.pipe.move(sf::Vector2f(-pipeWidth, -pipeGap));
}