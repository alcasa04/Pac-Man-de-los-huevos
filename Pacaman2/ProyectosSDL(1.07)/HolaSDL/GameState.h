#pragma once
/*#include"Game.h"
#include"Ghost.h"
#include"PacMan.h"
#include"SmartGhost.h"*/
#include<vector>
#include"GameObject.h"
#include"Ghost.h"
#include"SmartGhost.h"
#include"PacMan.h"

using namespace std;

//class GameStateMachine;

class GameState //: public GameObject
{
protected:

	Game* gueim = nullptr;

	GameMap* map = nullptr;

	PacMan* pac = nullptr;

	Ghost* ghosts[4];

	vector<SmartGhost*> enemies;

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
	virtual void render();
	GameState(Game* game);
	~GameState();
	//bool SetMap(string filename);
	virtual void Update();
	virtual void HandleEvent(SDL_Event& e);
};

