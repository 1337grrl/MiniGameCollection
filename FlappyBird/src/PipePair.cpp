#include "PipePair.h"
#include "StateMachine.h"


extern const float WINDOW_WIDTH = 1280;
extern const float WINDOW_HEIGHT = 720;

void PipePair::spawn() {
	calculateSpawnPosition();
	lowerPipe.init(spawnPosition);
	upperPipe.init(spawnPosition);

	pipeWidth = gTextures.pipe.getSize().x * gTextures.scaleWidth;
	rotate(upperPipe);

}

void PipePair::update() {
	move();
}

void PipePair::render() {
	lowerPipe.draw();
	upperPipe.draw();
}

void PipePair::rotate(Pipe& p) {
	p.pipe.setRotation(180);
	p.pipe.move(sf::Vector2f(pipeWidth, -pipeGap));
}


void PipePair::calculateSpawnPosition() {
	spawnPosition = sf::Vector2f(WINDOW_WIDTH, random(WINDOW_HEIGHT*.35f, WINDOW_HEIGHT *.85f));
}

void PipePair::move() {
	lowerPipe.move(pipeSpeed);
	upperPipe.move(pipeSpeed);
}

int PipePair::random(int min, int max) {
	return min + (rand() % (max - min));
}

sf::Vector2f PipePair::getPosition() { return lowerPipe.pipe.getPosition(); }