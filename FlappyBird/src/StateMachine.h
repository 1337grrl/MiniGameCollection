#pragma once

#include <SFML/Graphics.hpp>
#include "TexturePack.h"
#include "states/State.h"
#include "states/StartState.h"
#include "states/CountdownState.h"
#include "states/PlayState.h"
#include "states/ScoreState.h"
#include "Background.h"
#include "Bird.h"
#include "PipePair.h"
#include <map>

class StateMachine {
public:
	State* state;

	// Enum + map
	enum class StateNames { start, countdown, play, score, count };
	std::map<StateNames, State*> states;
	StateNames nextState = StateNames::count;

	
	void init(sf::RenderWindow* w);
	void handleInput();
	void update();
	void render();

	void registerState(StateNames sn, State* s);
	void setState(StateNames sn);


private:
	sf::RenderWindow* window;

	sf::Clock deltaClock;
	float delta;

	TexturePack textures;

	Background background;
	Bird bird;



	const float SCALE_WIDTH = 2.5f;
	const float SCALE_HEIGHT = 2.5f;
	const sf::Vector2f SCALE = sf::Vector2f(SCALE_WIDTH, SCALE_HEIGHT);

	void getDelta();
};

extern StateMachine gStateMachine;
