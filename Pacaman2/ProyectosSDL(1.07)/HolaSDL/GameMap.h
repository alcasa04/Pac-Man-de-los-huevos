#pragma once
#include<iostream>
#include<string>
#include"PacMan.h"
#include"Texture.h"
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"

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

class GameMap : public GameObject
{
	friend class Game;
	//Game puede acceder a campos privados de GameMap
private:
	//Game* game = nullptr;

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

	GameMap(int fils, int cols, SDL_Renderer* render);
	//constructora que crea un tablero de fils X cols

	~GameMap();
	//destructora

	MapCells GetCell(int x, int y);
	//da que hay en una casilla determinada (elementos estaticos solo)

	void SetCell(int x, int y, MapCells cell);
	//cambia el contenido de una casilla (elementos estaticos solo)

	void Renderizado(SDL_Rect rect, int tipo);

	void AnimVit();

	bool loadFromFile(string filename);
	void Render();
	void update();
	bool saveToFile(string filename);
};

