#pragma once

#include <list>
#include <deque>

#include "StateMachine.h"


// --- Window Constants ---
const float WINDOW_WIDTH = 1280;
const float WINDOW_HEIGHT = 720;
const sf::Vector2f WINDOW_CENTER = sf::Vector2f(WINDOW_WIDTH * .5f, WINDOW_HEIGHT * .5f);


// --- Global Variables ---
sf::RenderWindow gWindow;
TexturePack gTextures;
Background gBackground;
Bird gBird;
StateMachine gStateMachine;
int gScore;



void setupWindow() {
	gWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FLAPPY BIRD", sf::Style::Default);
	gWindow.setFramerateLimit(60);
}


void load() {
	setupWindow();
	gTextures.init();
	gBackground.init();
	gBird.init();
	gStateMachine.init();
}


int main() {
	load();

	while (gWindow.isOpen()) {

		gStateMachine.handleInput();

		gStateMachine.update();

		gStateMachine.render();
	}
}
