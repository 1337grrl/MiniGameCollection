#include "State.h"

void State::shouldWindowClose(sf::RenderWindow* w) {
	{
		sf::Event e;

		while (w->pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				w->close();
			}
		}
	}
}