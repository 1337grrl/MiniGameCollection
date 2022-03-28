#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <list>
#include <deque>


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
const sf::Vector2f ANTI_GRAVITY = sf::Vector2f(0.f, -25.f);

int random(int min, int max) {

	return min + (rand() % (max - min));
}

class TexturePack {
public:
	sf::Texture bird;
	sf::Texture ground;
	sf::Texture background;
	sf::Texture pipe;

	void init() {
		if (!bird.loadFromFile("content/bird.png")) {
			std::cerr << "Failed to load bird texture." << std::endl;
		}
		if (!ground.loadFromFile("content/ground.png")) {
			std::cerr << "Failed to load ground texture." << std::endl;
		}
		if (!background.loadFromFile("content/background.png")) {
			std::cerr << "Failed to load background texture." << std::endl;
		}
		if (!pipe.loadFromFile("content/pipe.png")) {
			std::cerr << "Failed to load pipe texture." << std::endl;
		}
	}
};
TexturePack textures;
std::list<sf::Sprite*> sprites;
sf::Sprite background;
constexpr int BG_WIDTH = 1032;
sf::Sprite ground;
int GROUND_Y_POSITION;


class Bird {
public:
	sf::Sprite body;

	void init() {
		body.setTexture(textures.bird);
		body.setOrigin(body.getLocalBounds().width * .5, body.getLocalBounds().height * .5f);
		body.setPosition(CENTER);
		body.setScale(spriteScale);
	}

	void move() {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			body.move(ANTI_GRAVITY);
		}
		body.move(GRAVITY * float(delta));
	}

};
Bird bird;


class Pipe {
public: 
	sf::Sprite upperPipe;
	sf::Sprite lowerPipe;

	float pipeWidth;
	sf::Vector2f PIPE_DISTANCE;


	void init() {
		sf::Vector2f pipePosition = sf::Vector2f(WINDOW_WIDTH, random(WINDOW_HEIGHT * .4, WINDOW_HEIGHT * .85f));
		lowerPipe.setTexture(textures.pipe);
		lowerPipe.setScale(spriteScale * .7f);
		lowerPipe.setPosition(pipePosition);

		pipeWidth = lowerPipe.getLocalBounds().width *(spriteScale.x*.7f*.5f);
		PIPE_DISTANCE = sf::Vector2f(pipeWidth, -WINDOW_HEIGHT * .2f);

		upperPipe.setTexture(textures.pipe);
		upperPipe.setScale(spriteScale * .7f);
		upperPipe.setPosition(pipePosition);
		upperPipe.move(PIPE_DISTANCE*2.f);
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
};


class PipeManager {
public:
	std::deque<Pipe> pipes;
	float pipeWidth;

	void spawnPipe() {
		if (frameCounter % 80 == 0) {
			Pipe pipe;
			pipe.init();
			pipes.push_back(pipe);
			frameCounter = 0;
			pipeWidth = pipe.pipeWidth;
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

	void drawPipes() {
		for (Pipe s : pipes) {
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
}

void getDelta() {
	delta = deltaClock.getElapsedTime().asSeconds();
	deltaClock.restart();
}

void update() {

	getDelta();
	frameCounter++;

	isWindowClosed();
	
	if (shouldReset()) {
		reset();
	}

	moveBackground();
	pMgr.spawnPipe();	
	pMgr.updatePipePositions();
	bird.move();
}


void render() {
	for (sf::Sprite* s : sprites) {
		window.draw(*s);
	}
	pMgr.drawPipes();
	window.display();
}


int main() {

	load();

	while (window.isOpen()) {

		update();

		render();

	}
}