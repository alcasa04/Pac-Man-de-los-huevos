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
	vector<GameCharacter*> aux;
	for (int i = 0; i < aux.size(); i++)
	{
		aux.pop_back();
	}
	for (int i = 0; i < objetos.size(); i++)
	{
		list<GameCharacter*>::iterator it = objetos.begin();
		advance(it, i);
		aux.push_back(*it);
		aux[i]->Render();
	}
}

void GameState::Update() 
{
	render();
	mover();
}

void GameState::HandleEvent(SDL_Event& evento) 
{

}
void GameState::mover()
{
	vector<GameCharacter*> aux;
	for (int i = 0; i < aux.size(); i++)
	{
		aux.pop_back();
	}
	for (int i = 0; i < objetos.size(); i++)
	{
		list<GameCharacter*>::iterator it = objetos.begin();
		advance(it, i);
		aux.push_back(*it);
		aux[i]->Mueve(Fils, Cols);
	}
}