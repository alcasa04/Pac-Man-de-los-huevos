#include "MenuState.h"

#include"PlayState.h"
#include"GameStateMachine.h"


MenuState::MenuState():GameState()
{
	SDL_Rect auxRect;

	auxRect.x = winWidth / 2 - 50;
	auxRect.w = 100;
	auxRect.h = 50;

	auxRect.y = winHeight / 2 - 100;
	MenuButtons.push_back(new Button(auxRect, new Texture(), gueim, GoToPlay, "..\\images\\azul.png"));

	auxRect.y += 100;
	MenuButtons.push_back(new Button(auxRect, new Texture(), gueim, LoadGame, "..\\images\\verde.png"));

	auxRect.y += 100;
	MenuButtons.push_back(new Button(auxRect, new Texture(), gueim, Exit, "..\\images\\rojo.png"));
}


MenuState::~MenuState()
{
	for (int i = 0; i < MenuButtons.size(); i++)
		delete MenuButtons[i];
}

void MenuState::GoToPlay(Game* game) {
	//gueim->newState(new PlayState());
	game->newState(new PlayState());
}

void MenuState::Exit(Game* game) {
	game->getMachine()->PopState();
}

void MenuState::LoadGame(Game* game) {
	game->newState(new PlayState());
	game->LoadFromFile();
}

void MenuState::render() {
	for (int i = 0; i < MenuButtons.size(); i++)
		MenuButtons[i]->Render();
	SDL_RenderPresent(gueim->getRender());
}

void MenuState::Update(){}

void MenuState::HandleEvent(SDL_Event& e) {
	for (int i = 0; i < MenuButtons.size(); i++)
		MenuButtons[i]->HandleEvent(e);
}