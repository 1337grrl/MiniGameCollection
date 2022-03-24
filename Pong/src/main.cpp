#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <deque>

sf::RenderWindow window;
constexpr float WINDOW_WIDTH = 1024.f;
constexpr float WINDOW_HEIGHT = 768.f;
const sf::Vector2f center = sf::Vector2f(WINDOW_WIDTH * .5f, WINDOW_HEIGHT * .5f);
constexpr float PADDING = 20.f;
enum class Side {left, right};


enum class State {start, running, lost, won};
State gameState = State::start;


std::deque<sf::Text> startScreen;
std::deque<sf::Text> inGameMessages;


class Stats {
public: 

	int lives;
	int points;

	void reset() {
		lives = 3;
		points = 0;
	}
};

// --- MAth Helpers ---
float magnitude(const sf::Vector2f& v) {
	return sqrt(v.x * v.x + v.y * v.y);
}


void normalize(sf::Vector2f& v) {
	if (magnitude(v))	
		v = v / magnitude(v);
}


class Token {
public: 
	sf::RectangleShape body;
	sf::Vector2f size;
	float speed;


	virtual void update() {	}
};
std::deque<Token> gameTokens;



class Paddle : public Token {
public:

	Side side;

	void init(const Side position) {

		// Init body
		size = sf::Vector2f(20, 100);
		body = sf::RectangleShape(size);
		body.setFillColor(sf::Color::White);

		// Init position
		side = position;
		reset();

		// Init motion
		speed = 5.f;

		// Init stats
	}

	void reset() {
		if (side == Side::left) {
			body.setPosition(PADDING, PADDING);
		}
		else {
			body.setPosition(WINDOW_WIDTH - PADDING - size.x, WINDOW_HEIGHT - PADDING - size.y);
		}
	}

	sf::Vector2f getPosition() {
		return body.getPosition();
	}

	sf::Vector2f getSize() {
		return body.getSize();
	}

	void setPosition(const sf::Vector2f p) {
		body.setPosition(p);
	}

	void setSize(const sf::Vector2f& size) {
		body.setSize(size);
	}

	void setSpeed(const float s) {
		speed = s;
	}

	void moveUp() {
		if (getPosition().y > 0)
			setPosition(getPosition() - sf::Vector2f(0.f, 1.f) * speed);
	}
	void moveDown() {
		if (getPosition().y + size.y  < WINDOW_HEIGHT)
			setPosition(getPosition() + sf::Vector2f(0.f, 1.f) * speed);
	}

	void update() {

	}

};
Paddle leftPad, rightPad;


class Ball : public Token {
public: 

	sf::Vector2f direction;

	void init() {
		// Init body
		size = sf::Vector2f(15.f, 15.f);
		body = sf::RectangleShape(size);
		body.setFillColor(sf::Color::White);

		// Init position
		body.setOrigin(size*.5f);
		setPosition(center);

		// Init motion
		speed = 4.f;
		initDirection();
	}

	// Something is off here...
	void initDirection() {

		srand(time(nullptr));
		int x = rand();
		direction = sf::Vector2f(x, (RAND_MAX - x));
		if (x % 4 == 0) {
			direction.x = -direction.x;
		}
		else if (x % 4 == 1) {
			direction.y = -direction.y;
		}
		else if (x % 4 == 2) {
			direction.x = -direction.x;
			direction.y = -direction.y;
		}
		normalize(direction);
	}

	void reset() {
		initDirection();
		setPosition(center);
	}

sf::Vector2f getPosition() {
	return body.getPosition();
}

void setPosition(const sf::Vector2f position) {
	body.setPosition(position);
}

bool wallCollisionDetected() {
	if (getPosition().y <= 0 || getPosition().y >= WINDOW_HEIGHT) {
		return true;
	}
	return false;
}

void changeVerticalDirection() {
	direction.y = -direction.y;
}

// Hier stimmt was nich...
void move() {
	sf::Vector2f position = getPosition();
	position += direction * speed;
	setPosition(position);

	if (wallCollisionDetected()) {
		changeVerticalDirection();
	}
}

void update() {
	if (gameState == State::running)
		move();
}
};
Ball ball;


sf::Font inGameFont;
sf::Text renderMsg(const std::string& msg, const sf::Font& font, const sf::Vector2f& position = sf::Vector2f(0.f, 0.f), uint8_t size = 10, sf::Color color = sf::Color::White, bool setORiginToMidpoint = true) {
	sf::Text message;

	message.setString(msg.c_str());
	message.setFont(font);
	message.setCharacterSize(size);
	if (setORiginToMidpoint) {
		message.setOrigin(message.getLocalBounds().width * .5f, message.getLocalBounds().height * .5f);
	}
	message.setPosition(position);
	message.setFillColor(color);

	return message;
}



void load() {

	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG!", sf::Style::Default);
	window.setFramerateLimit(60);

	if (!inGameFont.loadFromFile("content/font_ingame.ttf")) {
		std::cerr << "Font could not be loaded." << std::endl;
	}

	sf::Text title = renderMsg("PONG!", inGameFont, sf::Vector2f(WINDOW_WIDTH * .5, PADDING), 100);
	startScreen.push_back(title);
	sf::Text instructions = renderMsg("Click to start Game", inGameFont, sf::Vector2f(WINDOW_WIDTH * .5, PADDING + 110), 30);
	startScreen.push_back(instructions);


	leftPad.init(Side::left);
	gameTokens.push_front(leftPad);
	rightPad.init(Side::right);
	gameTokens.push_back(rightPad);
	ball.init();
	gameTokens.push_back(ball);
}

void reset() {
	if (gameState == State::running) {
		gameState = State::start;
	}
	leftPad.reset();
	rightPad.reset();
	ball.reset();
}

void takeInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		reset();
	}
	if (gameState == State::start) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			gameState = State::running;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		leftPad.moveUp();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		leftPad.moveDown();
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		rightPad.moveUp();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		rightPad.moveDown();
	}
}

void updateTokens() {
	//for (Token t : gameTokens) {
	//	t.update();
	//}
	ball.update();
	leftPad.update();
	rightPad.update();
}

void renderTokens() {
	if (gameState == State::start) {
		for (sf::Text t : startScreen) {
			window.draw(t);
		}
	}
	else if (gameState == State::running) {
		for (sf::Text m : inGameMessages) {
			window.draw(m);
		}
	}
	//for (Token t : gameTokens) {
	//	window.draw(t.body);
	//}
	window.draw(ball.body);
	window.draw(leftPad.body);
	window.draw(rightPad.body);
}



int main()
{


	// --- Load Game ---
	load();


	// --- Game Loop ---
	while (window.isOpen()) {

		// --- Check if window was closed or resized ---
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::Resized) {
				sf::Vector2u size = sf::Vector2u(event.size.width, event.size.height);
				window.setSize(size);
			}
		}

		// --- Update ---
		//updateTokens();
		takeInput();
		ball.update();

		// --- Render ---
		window.clear(sf::Color::Black);

		// Hier stimmt was nich!
		renderTokens();
		window.display();

	}
}
