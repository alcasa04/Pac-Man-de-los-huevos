#include "GameMap.h"
#include<iostream>
#include<fstream>
#include"Game.h"


GameMap::GameMap(int fils, int cols, SDL_Renderer* rend, PlayState*plai) : PacManObject()
//constructora, le pasamos como parametros filas y columnas del mapa
{
	play = plai;
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
	return tablero[x][y];
	//info de una celda determinada
}
//Devuelve qué tipo de casilla es la proporcionada por la X e Y

void GameMap::SetCell(int x, int y, MapCells cell) {
	tablero[x][y] = cell;
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

bool GameMap::loadFromFile(ifstream& archivo) {
	int aux = 0;
	archivo >> Fils >> Cols;
	if (Fils <= 0 || Cols <= 0)
		return false;
	tablero = new MapCells*[Fils];
	for (int i = 0; i < Fils; i++) {
		tablero[i] = new MapCells[Cols];
		for (int j = 0; j < Cols; j++) {
			archivo >> aux;
			if (aux < 0 || aux >5)
				return false;
			tablero[i][j] = (MapCells)aux;
		}
	}
	return !archivo.fail();
};

void GameMap::Render() {

	destRec.w = destRec.h = 20;
	//altura de la pantalla 600, numero de filas ~= 30, 600/30 = 20

	for (int j = 0; j < Fils; j++)
	{

		destRec.y = j * 20 + ((winHeight - 20 * Cols) / 2);
		//vamos situando donde vamos a pintar (en este caso la fila)

		for (int i = 0; i < Cols; i++)
		{
			//recorrido de la matriz entera

			destRec.x = (i * 20) + ((winWidth - 20 * Cols) / 2);
			//asignamos en que columna se va a pintar

			if (tablero[j][i] == Muro) {
				Renderizado(destRec, 0);
			}
			//si es un muro, renderizamos la imagen del muro

			else if (tablero[j][i] == Comida) {
				Renderizado(destRec, 1);
			}
			//analogo para la comida

			else if (tablero[j][i] == Vitamina) {
				 Renderizado(destRec, 2);
			}
			//analogo para la vitamina
		}
	}
};

void GameMap::update() {};

bool GameMap::saveToFile(ofstream& archivo) {
	archivo << Fils << " " << Cols<<endl;
	for (int i = 0; i < Fils; i++) {
		for (int j = 0; j < Cols; j++) {
			archivo << tablero[i][j];
			if (j != Cols)
				archivo << " ";
		}
		archivo << endl;
	}
	archivo << endl;

	return !archivo.fail();
};