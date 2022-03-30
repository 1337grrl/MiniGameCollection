#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <list>
#include <deque>

#include "TexturePack.h"
#include "Bird.h"
#include "PipePair.h"


enum class State {start, countdown, running, score};

sf::RenderWindow window;
constexpr float WINDOW_WIDTH = 1280;
constexpr float WINDOW_HEIGHT = 720;
const sf::Vector2f CENTER = sf::Vector2f(WINDOW_WIDTH * .5f, WINDOW_HEIGHT * .5f);

sf::Clock deltaClock;
sf::Clock spawnClock;
float delta;
int frameCounter = 0;

const sf::Vector2f spriteScale = sf::Vector2f(2.5f, 2.5f);

constexpr int BACKGROUND_SPEED = 100;
constexpr int GROUND_SPEED = 150;
constexpr int PIPE_SPEED = 400;

const sf::Vector2f GRAVITY = sf::Vector2f(0.f, 250.f);
const sf::Vector2f ANTI_GRAVITY = sf::Vector2f(0.f, -15.f);

bool scrolling = true;
int score = 0;

int random(int min, int max) {

	return min + (rand() % (max - min));
}

TexturePack textures;
std::list<sf::Sprite*> sprites;
sf::Sprite background;
constexpr int BG_WIDTH = 1032;
sf::Sprite ground;
int GROUND_Y_POSITION;



Bird bird;


class PipePair {
public: 
	sf::Sprite upperPipe;
	sf::Sprite lowerPipe;

	float pipeWidth;
	float pipeHeight;
	sf::Vector2f PIPE_GAP = sf::Vector2f(0.f, -WINDOW_HEIGHT * .4f);
	bool birdHasPassed = false;


	void init(const sf::Vector2f& positionPreviousPipe = sf::Vector2f(WINDOW_WIDTH, random(WINDOW_HEIGHT*.4f, WINDOW_HEIGHT*.85f))) {

		lowerPipe.setTexture(textures.pipe);
		lowerPipe.setScale(spriteScale);

		pipeWidth = lowerPipe.getLocalBounds().width * (spriteScale.x);
		pipeHeight = lowerPipe.getLocalBounds().height * (spriteScale.x);
		PIPE_GAP.x = pipeWidth;

		sf::Vector2f pipePosition;
		float yPosition = random(positionPreviousPipe.y - pipeHeight * .5f, positionPreviousPipe.y + pipeHeight * .5f);
		while (!(yPosition < GROUND_Y_POSITION - pipeHeight*.1f && yPosition > 100 + pipeHeight*.2f)) {
			yPosition = random(positionPreviousPipe.y - pipeHeight * .5f, positionPreviousPipe.y + pipeHeight * .5f);
		}
		pipePosition = sf::Vector2f(WINDOW_WIDTH, yPosition);

		lowerPipe.setPosition(pipePosition);


		upperPipe.setTexture(textures.pipe);
		upperPipe.setScale(spriteScale);
		upperPipe.setPosition(pipePosition);
		upperPipe.move(PIPE_GAP);
		upperPipe.setRotation(180);
	}

	sf::Vector2f getPosition() {
		return lowerPipe.getPosition();
	}

	void setPosition(const sf::Vector2f& p) {
		lowerPipe.setPosition(p);
		upperPipe.setPosition(p);
	}

	void move(const sf::Vector2f& p) {
		upperPipe.move(p);
		lowerPipe.move(p);
	}

	void draw() {
		window.draw(upperPipe);
		window.draw(lowerPipe);
	}

	bool collisionDetected() {
		if (bird.getPosition().y < getPosition().y && bird.getPosition().y > getPosition().y + PIPE_GAP.y) {
			return false;
		} 
		if (bird.getPosition().x < getPosition().x || bird.getPosition().x > getPosition().x + pipeWidth) {
			return false;
		}
		return true;
	}
};


class PipeManager {
public:
	std::deque<PipePair> pipes;
	float pipeWidth;

	void spawnPipe() {
		if (frameCounter % 80 == 0) {
			PipePair pipePair;
			if (!pipes.empty())
				pipePair.init(pipes.back().getPosition());
			else
				pipePair.init();
			pipes.push_back(pipePair);
			frameCounter = 0;
			pipeWidth = pipePair.pipeWidth;
		}
	}

	void updatePipePositions() {
		for (int i = 0; i < pipes.size(); ++i) {
			pipes[i].move(sf::Vector2f(-(int(PIPE_SPEED * delta) % int(WINDOW_WIDTH)), 0.f));
		}
		if (!pipes.empty() && pipes.front().getPosition().x < -pipeWidth *2.f) {
			pipes.pop_front();
		}
	}

	void update() {
		updatePipePositions();
		for (int i = 0; i < pipes.size(); ++i) {
			if (pipes[i].collisionDetected()) {
				scrolling = false;
			}
			else if (pipes[i].getPosition().x + pipeWidth + bird.body.getLocalBounds().width < CENTER.x && !pipes[i].birdHasPassed) {
				score++;
				pipes[i].birdHasPassed = true;
			}
		}
	}


	void drawPipes() {
		for (PipePair s : pipes) {
			s.draw();
		}
	}

};
PipeManager pMgr;


void moveBackground() {
	sf::Vector2f backgroundScroll, groundScroll;
	backgroundScroll = sf::Vector2f(-(int(BACKGROUND_SPEED * delta) % BG_WIDTH), 0.f);
	groundScroll = sf::Vector2f(-(int(GROUND_SPEED * delta) % int(WINDOW_WIDTH)), 0.f);

	if (background.getPosition().x <= -BG_WIDTH) {
		background.setPosition(sf::Vector2f(0.f, 0.f));
	}
	else {
		background.move(backgroundScroll);
	}
	if (ground.getPosition().x <= -WINDOW_WIDTH) {
		ground.setPosition(sf::Vector2f(0.f, GROUND_Y_POSITION));
	}
	else {
		ground.move(groundScroll);
	}
}

void setupWindow() {
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FLAPPY BIRD", sf::Style::Default);
	window.setFramerateLimit(60);
}

void setupGame() {
	textures.init();
	background.setTexture(textures.background);
	background.setScale(spriteScale);
	sprites.push_back(&background);

	ground.setTexture(textures.ground);
	ground.setScale(spriteScale);
	GROUND_Y_POSITION = WINDOW_HEIGHT - ground.getLocalBounds().height * spriteScale.x;
	ground.setPosition(sf::Vector2f(0.f, GROUND_Y_POSITION));
	sprites.push_back(&ground);

	bird.init();
	sprites.push_back(&bird.body);
}

void load() {

	srand(time(NULL));

	setupWindow();
	setupGame();
}


bool shouldReset() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		return true;

	}
	return false;
}

void isWindowClosed() {
	sf::Event e;

	while (window.pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			window.close();
		}
	}
}

void reset() {
	sprites.clear();
	pMgr.pipes.clear();
	setupGame();
	scrolling = true;
	score = 0;
}

void getDelta() {
	delta = deltaClock.getElapsedTime().asSeconds();
	deltaClock.restart();
}

void displayScorce() {
	sf::Text msg;

	msg.setString(std::to_string(score));
	msg.setFont(textures.font);
	msg.setCharacterSize(50);
	msg.setPosition(50.f, 50.f);

	window.draw(msg);
}

void update() {
 	isWindowClosed();
	if (scrolling) {

		getDelta();
		frameCounter++;

		moveBackground();
		pMgr.spawnPipe();
		pMgr.update();
		bird.move();
	}		
	if (shouldReset()) {
		reset();
	}
}


void render() {
	for (sf::Sprite* s : sprites) {
		window.draw(*s);
	}
	pMgr.drawPipes();
	displayScorce();
	window.display();
}


int main() {

	load();

	while (window.isOpen()) {

		update();

		render();

	}
}