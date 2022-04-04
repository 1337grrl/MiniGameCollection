#pragma once

#include <SFML/Graphics.hpp>

enum class RETURN_VALUE {SUCCESS, FAILURE};

class Window {
public:
	Window(float w, float h);
	~Window();

	RETURN_VALUE init();

private: 
	std::unique_ptr<sf::RenderWindow> m_Window;
	const float m_WINDOW_WIDTH;
	const float m_WINDOW_HEIGHT;
};
