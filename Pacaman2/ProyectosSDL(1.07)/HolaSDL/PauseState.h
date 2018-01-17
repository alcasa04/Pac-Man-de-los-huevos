#pragma once
#include"GameState.h"
#include"Button.h"

class PauseState:public GameState
{
private:
	vector<Button*> pauseButtons;
public:
	PauseState(Game* game);
	~PauseState();

	static void Resume(Game* game);
	static void GoToMenu(Game* game);
	static void Save(Game* game);

	virtual void Update();
	virtual void render();
	virtual void HandleEvent(SDL_Event& e);
};

