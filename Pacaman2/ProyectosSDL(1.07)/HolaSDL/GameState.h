#pragma once
/*#include"Game.h"
#include"Ghost.h"
#include"PacMan.h"
#include"SmartGhost.h"*/
#include<vector>
#include"GameObject.h"
#include "GameCharacter.h"
#include <list>

using namespace std;

//class GameStateMachine;

class GameState
{
protected:

	Game* gueim = nullptr;
	GameMap* map = nullptr;

	list<GameObject*> objetos;

	SDL_Rect destRec;
	SDL_Event evento;

	int winWidth = 800,
		winHeight = 600;
	int Fils = 0,
		Cols = 0;

	int Nivel = 1;
	int puntos = 0,
		maxPunt = 0;
	int ActComida = 0,
		MaxComida = 0;
public:
	GameState(Game* game);
	~GameState();
	virtual void render();
	virtual void update();
	virtual void HandleEvent(SDL_Event& e);
	//void mover();

};

