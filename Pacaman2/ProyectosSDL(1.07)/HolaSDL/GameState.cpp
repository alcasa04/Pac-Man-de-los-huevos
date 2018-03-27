#include "GameState.h"
#include"GameMap.h"


GameState::GameState(Game* game)// : GameObject()
{
	gueim = game;

}

GameState::~GameState()
{
}

//Comprueba las casillas del tablero, y llama al renderizado de cada una (al GameMap, al Pac-Man y a los Fantasmas)
void GameState::render() 
{
	for(GameObject* it: objetos)
	{
		it->Render();
	}
}

void GameState::update() 
{
	for (GameObject* it : objetos)
	{
		it->update();
	}
}

void GameState::HandleEvent(SDL_Event& evento) 
{
	for (GameObject* it : objetos)
	{
		it->HandleEvent(evento);
	}
}