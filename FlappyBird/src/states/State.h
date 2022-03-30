#pragma once

class State {
	virtual void enter() {}
	virtual void init() {}
	virtual void update() {}
	virtual void render() {}
	virtual void exit() {}
};
