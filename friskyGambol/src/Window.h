#pragma once

#include <SFML/Graphics.hpp>

class Window {
public:
	Window();
	~Window();

private: 
	const float m_WINDOW_WIDTH = 1280;
	const float m_WINDOW_HEIGHT = 720;
};
