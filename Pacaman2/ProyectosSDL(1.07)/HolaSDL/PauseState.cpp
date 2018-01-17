#include "PauseState.h"

#include"GameStateMachine.h"


PauseState::PauseState(Game* game):GameState(game)
{
	SDL_Rect auxRect;
	auxRect.x = winWidth / 2 - 50;
	auxRect.h = 50;
	auxRect.w = 100;

	auxRect.y = winHeight / 2 - 100;
	pauseButtons.push_back(new Button(auxRect, new Texture(), gueim, Resume, "..\\images\\azul.png"));

	auxRect.y += 100;
	pauseButtons.push_back(new Button(auxRect, new Texture(), gueim, Save, "..\\images\\verde.png"));

	auxRect.y += 100;
	pauseButtons.push_back(new Button(auxRect, new Texture(), gueim, GoToMenu, "..\\images\\rojo.png"));
}


PauseState::~PauseState()
{
	for (int i = 0; i < pauseButtons.size(); i++)
		delete pauseButtons[i];
}

void PauseState::GoToMenu(Game* game) {
	for (int i = 0; i < 2; i++)
		game->getMachine()->PopState();
}

void PauseState::Resume(Game* game) {
	game->getMachine()->PopState();
}

void PauseState::Save(Game* game) {
	//game->SaveToFile();
	for (int i = 0; i < 3; i++)
		game->getMachine()->PopState();
}

void PauseState::HandleEvent(SDL_Event& e) {
	for (int i = 0; i < pauseButtons.size(); i++)
		pauseButtons[i]->HandleEvent(e);
}

void PauseState::Update() {

}

void PauseState::render() {
	for (int i = 0; i < pauseButtons.size(); i++)
		pauseButtons[i]->Render();
	SDL_RenderPresent(gueim->getRender());
}