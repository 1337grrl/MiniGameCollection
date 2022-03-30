#pragma once

#include <SFML/Graphics.hpp>
#include "states/Start.h"


class StateMachine {
public:
	static Start* startState;
	static State* countDownState;
	static State* playState;
	static State* scoreState;

	void init();

	void changeState();

};