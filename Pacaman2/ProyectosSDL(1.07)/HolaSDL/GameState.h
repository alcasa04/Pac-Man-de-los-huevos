#pragma once
/*#include"Game.h"
#include"Ghost.h"
#include"PacMan.h"
#include"SmartGhost.h"*/
#include<vector>
#include"GameObject.h"
#include"Ghost.h"
#include"SmartGhost.h"

using namespace std;

//class GameStateMachine;

class GameState
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
public:
	virtual void render();
	GameState();
	~GameState();
	bool SetMap(string filename);
	virtual void Update();
	virtual void HandleEvent();
};

