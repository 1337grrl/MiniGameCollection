#pragma once

#include <SFML/Graphics.hpp>
#include "Pipe.h"

extern sf::RenderWindow gWindow;

class PipePair  {
public:
	Pipe lowerPipe;
	Pipe upperPipe;
	float pipeWidth;
	float pipeGap = gWindow.getSize().y * .4f;

	void spawn();
	void update();
	void render();

	float getPositionX() { return lowerPipe.pipe.getPosition().x; }
	sf::Vector2f getPosition();

private: 
	sf::Vector2f spawnPosition;
	bool birdHasPassed = false;
	const float pipeSpeed = -350;

	void rotate(Pipe& p);
	void calculateSpawnPosition();
	void move();
	int random(int min, int max);
};