#pragma once

#include <list>
#include <deque>

#include "StateMachine.h"


// --- Window Constants ---
constexpr float WINDOW_WIDTH = 1280;
constexpr float WINDOW_HEIGHT = 720;
const sf::Vector2f WINDOW_CENTER = sf::Vector2f(WINDOW_WIDTH * .5f, WINDOW_HEIGHT * .5f);


// --- Global Window + Global StateMachine ---
sf::RenderWindow gWindow;
StateMachine gStateMachine;


int frameCounter = 0;


void setupWindow() {
	gWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FLAPPY BIRD", sf::Style::Default);
	gWindow.setFramerateLimit(60);
}


void load() {
	setupWindow();
	gStateMachine.init(&gWindow);
}


int main() {
	load();

	while (gWindow.isOpen()) {

		gStateMachine.handleInput();

		gStateMachine.update();

		gStateMachine.render();
	}
}





/*
constexpr int PIPE_SPEED = 400;



bool scrolling = true;
int score = 0;

int random(int min, int max) {

	return min + (rand() % (max - min));
}

TexturePack textures;




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


bool shouldReset() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		return true;

	}
	return false;
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
		bird.update(delta);
	}		
	if (shouldReset()) {
		reset();
	}
}


void render() {
	pMgr.drawPipes();
	bird.render(window);
	displayScorce();
	window.display();
}


int main() {

	load();

	while (window.isOpen()) {

		update();

		render();

	}
}*/