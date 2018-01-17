#pragma once
#include"GameState.h"
#include"Button.h"

class MenuState:public GameState
{
private:
	vector<Button*> MenuButtons;
public:
	MenuState(Game* game);
	~MenuState();
	static void GoToPlay(Game* game);
	static void Exit(Game* game);
	static void LoadGame(Game* game);

	virtual void Update();
	virtual void render();
	virtual void HandleEvent(SDL_Event& e);
};

