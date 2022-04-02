#pragma once

#include <SFML/Graphics.hpp>
#include "Pipe.h"

extern sf::RenderWindow gWindow;

class PipePair  {
public:
	Pipe lowerPipe;
	Pipe upperPipe;
	float pipeWidth;

	void spawn();
	void update();
	void render();

	inline float getPositionX() { return lowerPipe.pipe.getPosition().x; }

private: 
	sf::Vector2f spawnPosition;
	bool birdHasPassed = false;
	const float pipeSpeed = -5;
	float pipeGap = gWindow.getSize().y * .4f;

	void rotate(Pipe& p);
	void calculateSpawnPosition();
	void move();
	int random(int min, int max);
};