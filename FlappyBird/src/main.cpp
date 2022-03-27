#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <list>
#include <vector>


sf::RenderWindow window;
constexpr float WINDOW_WIDTH = 1280;
constexpr float WINDOW_HEIGHT = 720;
const sf::Vector2f CENTER = sf::Vector2f(WINDOW_WIDTH * .5f, WINDOW_HEIGHT * .5f);

sf::Clock deltaClock;
sf::Clock spawnClock;
float delta;
int spawnTimer;

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
sf::Sprite ground;

class Bird {
public:
	sf::Sprite body;

	void init() {
		body.setTexture(textures.bird);
		body.setOrigin(body.getLocalBounds().width * .5, body.getLocalBounds().height * .5f);
		body.setPosition(CENTER);
		body.scale(spriteScale);
	}

	void move() {
		sf::Vector2f tmp = body.getPosition();
		tmp += GRAVITY * float(delta);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			tmp += ANTI_GRAVITY;
		}
		body.setPosition(tmp);
	}

};
Bird bird;


class PipeManager {
public:
	std::vector<sf::Sprite> pipes;
	const sf::Vector2u size = textures.pipe.getSize();
	bool pipeJustSpawned = false;

	void spawnPipe() {
			sf::Sprite pipe;
			pipe.setTexture(textures.pipe);
			pipe.scale(spriteScale * .7f);
			pipe.setPosition(sf::Vector2f(WINDOW_WIDTH, random(WINDOW_HEIGHT * .25, WINDOW_HEIGHT - 25.f)));
			pipes.push_back(pipe);
			pipeJustSpawned = true;
	}

	void update() {
		for (int i = 0; i < pipes.size(); ++i) {
			sf::Vector2f tmp = pipes[i].getPosition();
			if (tmp.x < 0 - size.x) {
				;
			}
			else {
				pipes[i].setPosition(tmp + sf::Vector2f(-(int(PIPE_SPEED * delta) % int(WINDOW_WIDTH)), 0.f));
			}
		}
	}

	void draw() {
		for (sf::Sprite s : pipes) {
			if (s.getPosition().x > 0 - size.x) {
				window.draw(s);
			}
		}
	}

	void reset() {

	}
};
PipeManager pMgr;

void reset() {

}

void moveBackground() {
	sf::Vector2f backgroundScroll, groundScroll;
	backgroundScroll = sf::Vector2f(-(int(BACKGROUND_SPEED * delta) % 1032), 0.f);
	groundScroll = sf::Vector2f(-(int(GROUND_SPEED * delta) % int(WINDOW_WIDTH)), 0.f);

	background.setPosition(background.getPosition() + backgroundScroll);
	ground.setPosition(ground.getPosition() + groundScroll);
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

void load() {

	srand(time(NULL));

	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FLAPPY BIRD", sf::Style::Default);
	window.setFramerateLimit(60);


	textures.init();
	background.setTexture(textures.background);
	background.scale(spriteScale);
	sprites.push_back(&background);

	ground.setTexture(textures.ground);
	ground.scale(spriteScale);
	ground.setPosition(sf::Vector2f(0.f, WINDOW_HEIGHT - ground.getLocalBounds().height * spriteScale.x));
	sprites.push_back(&ground);

	bird.init();
	sprites.push_back(&bird.body);
}


void update() {
	delta = deltaClock.getElapsedTime().asSeconds();
	spawnTimer = int(spawnClock.getElapsedTime().asSeconds());
	deltaClock.restart();


	isWindowClosed();
	if (shouldReset()) {
		reset();
	}

	moveBackground();
	if (spawnTimer % 2 == 1 && !pMgr.pipeJustSpawned) {
		pMgr.spawnPipe();
	}
	else if (spawnTimer % 2 != 1 && pMgr.pipeJustSpawned) {
		pMgr.pipeJustSpawned = false;
	}
	bird.move();
	pMgr.update();
}


void render() {
	for (sf::Sprite* s : sprites) {
		window.draw(*s);
	}
	pMgr.draw();
	window.display();
}


int main() {

	load();

	while (window.isOpen()) {

		update();

		render();

	}
}