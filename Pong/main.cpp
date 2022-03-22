// Pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>

constexpr float WINDOW_WIDTH = 1024.f;
constexpr float WINDOW_HEIGHT = 768.f;




int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG!");
	window.setFramerateLimit(60);

	window.clear(sf::Color::Black);
	window.display();

	char x;
	std::cin >> x;
}
