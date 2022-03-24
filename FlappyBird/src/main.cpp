#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <list>


sf::RenderWindow window;
constexpr float WINDOW_WIDTH = 1280;
constexpr float WINDOW_HEIGHT = 720;
const sf::Vector2f CENTER = sf::Vector2f(WINDOW_WIDTH * .5f, WINDOW_HEIGHT * .5f);

sf::Clock Clock;
sf::Int32 delta;

const sf::Vector2f spriteScale = sf::Vector2f(2.5f, 2.5f);
constexpr int BACKGROUND_SPEED = 3;
constexpr int GROUND_SPEED = 6;

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


void reset() {

}

void moveBackground() {
	sf::Vector2f backgroundScroll, groundScroll;
	backgroundScroll = sf::Vector2f(-(BACKGROUND_SPEED * delta % 1032), 0.f);
	groundScroll = sf::Vector2f(-(GROUND_SPEED * delta % int(WINDOW_WIDTH)), WINDOW_HEIGHT - ground.getLocalBounds().height * spriteScale.x);

	background.setPosition(backgroundScroll);
	ground.setPosition(groundScroll);
}

void takeInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		reset();
	}
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
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FLAPPY BIRD", sf::Style::Default);
	window.setVerticalSyncEnabled(true);


	textures.init();
	background.setTexture(textures.background);
	background.scale(spriteScale);
	sprites.push_back(&background);

	ground.setTexture(textures.ground);
	ground.scale(spriteScale);
	sprites.push_back(&ground);
}


void update() {
	delta = Clock.getElapsedTime().asMilliseconds()*.03;

	isWindowClosed();
	moveBackground();
}


void render() {
	for (sf::Sprite* s : sprites) {
		window.draw(*s);
	}
	window.display();
}


int main() {

	load();

	while (window.isOpen()) {

		update();

		render();

	}
}