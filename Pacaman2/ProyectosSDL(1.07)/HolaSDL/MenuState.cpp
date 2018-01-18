#include "MenuState.h"

#include"PlayState.h"
#include"GameStateMachine.h"


MenuState::MenuState(Game* game):GameState(game)
{
	gueim = game;
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

	text = new Texture();
	if (!text->loadText("..\\images\\Pac-Titulo.png", 1, 2, gueim->getRender()))gueim->error = true;
	destRec.y = 0;
	destRec.x = winWidth / 3;
	destRec.w = winWidth / 3;
	destRec.h = winHeight;
}


MenuState::~MenuState()
{
	for (int i = 0; i < MenuButtons.size(); i++)
		delete MenuButtons[i];
}

void MenuState::GoToPlay(Game* game) {
	//gueim->newState(new PlayState());
	game->newState(new PlayState(game));
}

void MenuState::Exit(Game* game) {
	game->getMachine()->PopState();
}

void MenuState::LoadGame(Game* game) {
	game->newState(new PlayState(game, 0));
	//game->LoadFromFile();
}

void MenuState::render() {
	SDL_RenderClear(gueim->getRender());
	//text->Render(1, 1, destRec, gueim->getRender());
	text->RenderFrame(0,0,destRec, gueim->getRender());
	for (int i = 0; i < MenuButtons.size(); i++)
		MenuButtons[i]->Render();
	SDL_RenderPresent(gueim->getRender());
}

void MenuState::Update(){}

void MenuState::HandleEvent(SDL_Event& e) {
	for (int i = 0; i < MenuButtons.size(); i++)
		MenuButtons[i]->HandleEvent(e);
}