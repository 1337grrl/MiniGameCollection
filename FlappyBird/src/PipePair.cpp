#include "PipePair.h"
#include "StateMachine.h"



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
	spawnPosition = sf::Vector2f(gWindow.getSize().x, random(gWindow.getSize().y*.35f, gWindow.getSize().y*.85f));
}

void PipePair::move() {
	lowerPipe.move(pipeSpeed);
	upperPipe.move(pipeSpeed);
}

int PipePair::random(int min, int max) {
	return min + (rand() % (max - min));
}