#pragma once

#include <SFML/Graphics.hpp>
#include "TexturePack.h"
#include "states/State.h"
#include "states/StartState.h"
#include "states/CountdownState.h"
#include "states/PlayState.h"
#include "states/ScoreState.h"
#include "Background.h"


class StateMachine {
public:
	
	void init(sf::RenderWindow* w, State* s);
	void update();
	void render();

private:
	State* state;

	sf::Clock deltaClock;
	float delta;

	sf::RenderWindow* window;


	TexturePack textures;
	Background background;

	const float SCALE_WIDTH = 2.5f;
	const float SCALE_HEIGHT = 2.5f;
	const sf::Vector2f SCALE = sf::Vector2f(SCALE_WIDTH, SCALE_HEIGHT);

	void getDelta();
};