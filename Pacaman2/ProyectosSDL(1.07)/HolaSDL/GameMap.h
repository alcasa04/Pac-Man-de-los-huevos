#pragma once
#include<iostream>
#include<string>
#include"PacMan.h"
#include"Texture.h"
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "PacManObject.h"

using namespace std;

class Game;

enum MapCells
{
	Vacio,
	Muro,
	Comida,
	Vitamina,
	Null,
};
//enumerable indicando todas las casillas disponibles en el juego

class GameMap : public PacManObject
{
	friend class GameState;
	friend class Game;
	//Game puede acceder a campos privados de GameMap
private:
	//Game* game = nullptr;

	int winWidth = 800,
		winHeight = 600;

	int Fils, Cols;
	//tamaño del tablero

	MapCells** tablero;
	//MapCells tab[];

	SDL_Rect destRec;
	//para localizar las casillas

	Texture* textura[3];

	SDL_Renderer* rendering = nullptr;
	int animVit = 0;

public:

	GameMap(int fils, int cols, SDL_Renderer* render, PlayState* play);
	//constructora que crea un tablero de fils X cols

	~GameMap();
	//destructora

	MapCells GetCell(int x, int y);
	//da que hay en una casilla determinada (elementos estaticos solo)

	void SetCell(int x, int y, MapCells cell);
	//cambia el contenido de una casilla (elementos estaticos solo)

	void Renderizado(SDL_Rect rect, int tipo);

	void AnimVit();

	virtual bool loadFromFile(ifstream& archivp);
	virtual void Render();
	virtual void update();
	virtual void Mueve() {};
	virtual bool HandleEvent(SDL_Event& evento) { return false; };
	virtual bool saveToFile(ofstream& archivo);

	MapCells** getTablero() { return tablero; };

	int getFils() { return Fils; };
	int getCOls() { return Cols; };
};

