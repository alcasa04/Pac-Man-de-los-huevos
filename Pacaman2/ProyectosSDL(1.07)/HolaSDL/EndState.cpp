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
	EndButton = new Button(auxRect, new Texture(), gueim, GoToMenu, "..\\images\\rojo.png");
}


EndState::~EndState()
{
}

void EndState::render() {
	EndButton->Render();
	SDL_RenderPresent(gueim->getRender());
}

void EndState::Update() {

}

void EndState::HandleEvent(SDL_Event& e) {
	EndButton->HandleEvent(e);
}

void EndState::GoToMenu(Game* game) {
	for (int i = 0; i < 2; i++)
		game->getMachine()->PopState();
}
