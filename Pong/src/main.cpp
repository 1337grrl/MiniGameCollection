#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>

sf::RenderWindow window;
constexpr float WINDOW_WIDTH = 1024.f;
constexpr float WINDOW_HEIGHT = 768.f;
const sf::Vector2f center = sf::Vector2f(WINDOW_WIDTH * .5f, WINDOW_HEIGHT * .5f);
constexpr float PADDING = 20.f;
enum class Side {left, right};


enum class State {start, running, lost, won, reset};
State gameState = State::start;


std::list<sf::Text> startScreen;
std::list<sf::Text> inGameMessages;




// --- Math Helpers ---
float magnitude(const sf::Vector2f& v) {
	return sqrt(v.x * v.x + v.y * v.y);
}


void normalize(sf::Vector2f& v) {
	if (magnitude(v))	
		v = v / magnitude(v);
}

int random(int min, int max) //range : [min, max]
{
	srand(time(NULL)); //seeding for the first time only!

	return min + rand() % ((max + 1) - min);
}


class Token {
public: 
	sf::RectangleShape body;
	sf::Vector2f size;
	float speed;


	virtual void update() {	}
};
std::list<Token*> gameTokens;



class Paddle : public Token {
public:

	Side side;
	int score;

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
		score = 0;
	}

	void reset() {
		if (side == Side::left) {
			body.setPosition(PADDING, PADDING);
		}
		else {
			body.setPosition(WINDOW_WIDTH - PADDING - size.x, WINDOW_HEIGHT - PADDING - size.y);
		}
	}

	const sf::Vector2f getPosition() {
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

		int x = random(-100, 100);
		int y = random(-abs(x)*.5f, abs(x)*.5f);
		direction = sf::Vector2f(x, y);

		normalize(direction);
	}

	void reset() {
		initDirection();
		setPosition(center);
		speed = 4.f;

	}

	const sf::Vector2f getPosition() {
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

	bool paddleCollisionDetected(Paddle& pad) {
		if (getPosition().x >= pad.getPosition().x + pad.size.x ||
			getPosition().x + size.x <= pad.getPosition().x ||
			getPosition().y >= pad.getPosition().y + pad.size.y ||
			getPosition().y + size.y <= pad.getPosition().y) {
			return false;
		}
		return true;
	}

	void changeHorizontalDirection() {
		direction.x = -direction.x;
	}

	void changeVerticalDirection() {
		direction.y = -direction.y;
	}

	void move() {
		sf::Vector2f position = getPosition();
		position += direction * speed;
		setPosition(position);

	}

	void update() {
		if (gameState == State::running)
			move();

		if (wallCollisionDetected()) {
			changeVerticalDirection();
		}

		if (paddleCollisionDetected(leftPad)) {
			sf::Vector2f offset = getPosition();
			offset.x + leftPad.size.x;
			setPosition(offset);
			changeHorizontalDirection();
			speed *= 1.05;
		}

		if (paddleCollisionDetected(rightPad)) {
			sf::Vector2f offset = getPosition();
			offset.x - rightPad.size.x;
			setPosition(offset);
			changeHorizontalDirection();
			speed *= 1.05;
		}
	}
};
Ball ball;


sf::Font inGameFont;
sf::Text renderMsg(const std::string& msg, const sf::Vector2f& position = sf::Vector2f(0.f, 0.f), uint8_t size = 30, const sf::Font& font= inGameFont, sf::Color color = sf::Color::White, bool setORiginToMidpoint = true) {
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

	sf::Text title = renderMsg("PONG!", sf::Vector2f(WINDOW_WIDTH * .5, PADDING), 100);
	startScreen.push_back(title);
	sf::Text instructions = renderMsg("Click to start Game", sf::Vector2f(WINDOW_WIDTH * .5, PADDING + 110));
	startScreen.push_back(instructions);



	leftPad.init(Side::left);
	gameTokens.push_front(&leftPad);
	rightPad.init(Side::right);
	gameTokens.push_back(&rightPad);
	ball.init();
	gameTokens.push_back(&ball);
}

void reset() {
	if (gameState == State::running) {
		gameState = State::reset;
	}
	leftPad.reset();
	rightPad.reset();
	ball.reset();
}

void takeInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		reset();
	}
	if (gameState == State::start || gameState == State::reset) {
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
	for (Token* t : gameTokens) {
		t->update();
	}
	takeInput();
	if (gameState == State::running) {
		if (ball.getPosition().x < 0) {
			rightPad.score++;
			reset();
		}
		if (ball.getPosition().x > WINDOW_WIDTH) {
			leftPad.score++;
			reset();
		}
	}

}

void renderTokens() {

	sf::Text leftScore = renderMsg(std::to_string(leftPad.score), center - sf::Vector2f(PADDING*7.f, PADDING * 5.f), 100);

	sf::Text rightScore = renderMsg(std::to_string(rightPad.score), center + sf::Vector2f(PADDING*7.f, -PADDING * 5.f), 100);

	if (gameState == State::start) {
		for (sf::Text t : startScreen) {
			window.draw(t);
		}
	}
	for (Token* t : gameTokens) {
		window.draw(t->body);
	}
	window.draw(leftScore);
	window.draw(rightScore);
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
		updateTokens();
		

		// --- Render ---
		window.clear(sf::Color::Black);
		renderTokens();
		window.display();

	}
}
