#pragma once
#include"GameState.h"

class PlayState:public GameState
{
private:
	int ActComida = 0,
		MaxComida = 0;

	int puntos = 0,
		maxPunt = 0,
		nivel = 1;
public:
	PlayState();
	~PlayState();
	virtual void render();
	virtual void Update();
	virtual void HandleEvents(SDL_Event& e);
	bool NextCell(int x, int y, int dir);
	bool SaveToFile();
	void FinJuego();
	void Colision();
	void CreaFantasma(int x, int y);
};

