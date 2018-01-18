#pragma once
#include"GameState.h"
#include"Button.h"
class EndState:public GameState
{
private:
	Button* EndButton;
public:
	EndState(Game* game);
	~EndState();
	virtual void Update();
	virtual void HandleEvent(SDL_Event& e);
	virtual void render();
	static void GoToMenu(Game*game);
};

