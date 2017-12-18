#include "GameMap.h"
#include<iostream>
#include<fstream>
#include"Game.h"


GameMap::GameMap(int fils, int cols, SDL_Renderer* rend) : GameObject()
//constructora, le pasamos como parametros filas y columnas del mapa
{
	Fils = fils;
	Cols = cols;
	//asignamos variables
	rendering = rend;
	tablero = new MapCells* [fils];
	//creamos un nuevo tablero que tiene fils filas

	for (int i = 0; i < Fils; i++) {

		tablero[i] = new MapCells[cols];
		//a cada fila le asignamos cols columnas, creando asi la matriz
	}
	for (int i = 0; i < 3; i++)
	{
		textura[i] = new Texture();
	}
	if (!textura[0]->loadText("..\\images\\wall2.png", 1, 1, rendering))gueim->error = true;
	//cargamos la textura 0 (muro) y si da error en la carga ponemos la bander a true

	else if (!textura[1]->loadText("..\\images\\food2.png", 1, 1, rendering))gueim-> error = true;
	//analogo para la comida

	else if (!textura[2]->loadText("..\\images\\burguer1.png", 1, 3, rendering)) gueim->error = true;
	//analogo para la vitamina
}
//Constructora de GameMap

GameMap::~GameMap()
//destructora
{
	if (tablero != nullptr) {
		//si no, no hay nada que destruir
		delete tablero;
	}
	for (int i = 0; i < 3; i++)
	{
		delete textura[i];
	}
}
//Destructora de GameMap

MapCells GameMap::GetCell(int x, int y) {
	return tablero[y][x];
	//info de una celda determinada
}
//Devuelve qué tipo de casilla es la proporcionada por la X e Y

void GameMap::SetCell(int x, int y, MapCells cell) {
	tablero[y][x] = cell;
	//cambiamos una casilla a la que le pasemos
}
//Cambia el tipo de casilla

void GameMap::Renderizado(SDL_Rect destRec, int tipo)
{
	if (tipo == 0)
		textura[0]->Render(destRec, rendering);
	else if(tipo == 1)
		textura[1]->Render(destRec, rendering);
	else if (tipo == 2)
	{
			textura[2]->RenderFrame(animVit, 0, destRec, rendering);
	}

}
//Pinta los muros, la comida y las vitaminas, almacenados en un array de Texturas

void GameMap::AnimVit()
{
	animVit= (animVit+1)%3;
}
//Cambia la animación de la vitamina

bool GameMap::loadFromFile(string filename) {
	return true;
};

void GameMap::Render() {};

void GameMap::update() {};

bool GameMap::saveToFile(string filename) {
	return true;
};