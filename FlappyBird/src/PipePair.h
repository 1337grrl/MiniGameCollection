#pragma once

#include <SFML/Graphics.hpp>
#include "Pipe.h"

class PipePair  {
public:
	Pipe lowerPipe;
	Pipe upperPipe;
	float pipeWidth;
	float pipeGap;

	PipePair();
	~PipePair();

	void init(const sf::Texture& t, float scaleWidth, float scaleHeight, const sf::Vector2f& p, float pG);
	void update(float delta);
	void render();

private: 
	void rotate(Pipe& p);
};