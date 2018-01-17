#pragma once
#include"GameState.h"

class EndState:public GameState
{
public:
	EndState(Game* game);
	~EndState();
	virtual void Update();
	virtual void HandleEvent();
	virtual void render();
};

