#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>


sf::RenderWindow window;
constexpr float WINDOW_WIDTH = 1280;
constexpr float WINDOW_HEIGHT = 720;
const sf::Vector2f CENTER = sf::Vector2f(WINDOW_WIDTH * .5f, WINDOW_HEIGHT * .5f);

const sf::Vector2f spriteScale = sf::Vector2f(2.5f, 2.5f);

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
	ground.setPosition(sf::Vector2f(0.f, WINDOW_HEIGHT - ground.getLocalBounds().height*spriteScale.x));
	sprites.push_back(&ground);
}


void update() {
	isWindowClosed();
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