#include "EndState.h"

#include"GameStateMachine.h"

EndState::EndState(Game* game):GameState(game)
{
	gueim = game;
	SDL_Rect auxRect;
	auxRect.x = winWidth / 2 - 50;
	auxRect.y = winHeight / 2 - 25;
	auxRect.w = 100;
	auxRect.h = 50;
	objetos.push_back(new Button(auxRect, new Texture(), gueim, GoToMenu, "..\\images\\exit.png"));
}

EndState::~EndState()
{
}

void EndState::render() {
	GameState::render();
}

void EndState::Update() {
	GameState::update();
}

void EndState::HandleEvent(SDL_Event& e) {
	GameState::HandleEvent(e);
}

void EndState::GoToMenu(Game* game) {
	for (int i = 0; i < game->getMachine()->getNumber(); i++)
	{
		game->getMachine()->PopState();
	}
}
