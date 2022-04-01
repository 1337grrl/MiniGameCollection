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
	TexturePack textures;

	// Enum + map
	enum class StateNames { start, countdown, play, score, count };
	std::map<StateNames, State*> states;
	StateNames nextState = StateNames::count;

	
	void init(sf::RenderWindow* w);
	void handleInput();
	void update();
	void render();

	void setState(StateNames sn);


private:
	sf::RenderWindow* window;

	sf::Clock deltaClock;
	float delta;


	Background background;

	const float SCALE_WIDTH = 2.5f;
	const float SCALE_HEIGHT = 2.5f;
	const sf::Vector2f SCALE = sf::Vector2f(SCALE_WIDTH, SCALE_HEIGHT);

	void getDelta();

	void registerState(StateNames sn, State* s);

	void shouldWindowClose(sf::RenderWindow* w);

};

extern sf::RenderWindow gWindow;
extern StateMachine gStateMachine;
extern Bird gBird;
extern const sf::Vector2f WINDOW_CENTER;
