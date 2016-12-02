#pragma once

class IState {
public:
	virtual ~IState() {}
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void resume() = 0;
	virtual void pause() = 0;
};