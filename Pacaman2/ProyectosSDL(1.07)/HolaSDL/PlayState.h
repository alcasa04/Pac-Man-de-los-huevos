#pragma once
#include"GameState.h"
#include "PacMan.h"
#include "Ghost.h"
#include "SmartGhost.h"

class PlayState:public GameState
{
private:
	PacMan* pac;
	vector<Ghost*> ghosts;
	vector<SmartGhost*> enemies;
public:
	PlayState(Game* game);
	PlayState(Game* game, int i);
	~PlayState();
	virtual void render();
	virtual void Update();
	void HandleEvent(SDL_Event& e);
	bool NextCell(int x, int y, int dir);
	bool SaveToFile();
	void FinJuego();
	void Colision();
	void CreaFantasma(int x, int y);
	bool SetMap(string filename);
	void GUI();

	int PacX() { return pac->getPosX(); };
	int PacY() { return pac->getPosY(); };
};

