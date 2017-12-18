#include "SmartGhost.h"
#include"Game.h"
#include"GameMap.h"
#include "PacMan.h"

SmartGhost::SmartGhost() : GameCharacter(0, 0, nullptr) {
	IniX = IniY = PosX = PosY = 0;
}
//constructora default que deja el fantasma en la posicion (0,0)

SmartGhost::SmartGhost(int x, int y, SDL_Renderer* rend, Game* game) : GameCharacter(x, y, game)
{

	PosX = IniX = x;
	PosY = IniY = y;
	dir = 0;
	render = rend;
	if (!text->loadText(("..\\images\\characters1.png"), 4, 14, render)) gueim->error = true;
}
//Constructora que situa al fantasma en una posicion dada

int SmartGhost::getPosX() {
	return PosX;
}
//Devuelve su X

int SmartGhost::getPosY() {
	return PosY;
}
//Devuelve su Y

SmartGhost::~SmartGhost()
{
	delete text;
}
//Destructora de Ghost

void SmartGhost::CambiaDir()
{

	if (edad < 20)
	{
		int auxDir = 0;
		int contador = 0;
		vector<int> posible;
		for (int i = 0; i < 4; i++)
		{
			if (gueim->NextCell(PosX, PosY, i) && i != (dir + 2) % 4)
			{
				contador++;
				posible.push_back(i);
			}

		}
		if (contador >= 1)
		{
			auxDir = rand() % contador;
			dir = posible[auxDir];
		}
		else if (contador == 0)
		{
			dir = (dir + 2) % 4;
		}
	}
	else
	{
		int contad = 0;
		int j = 0;
		float auxMax;
		float distancia = 200000;
		vector<int> posibl;
		for (int i = 0; i < 4; i++)
		{
			if (gueim->NextCell(PosX, PosY, i))
			{
				contad++;
				posibl.push_back(i);
			}
		}
		while (j < posibl.size())
		{
			int dirX;
			int dirY;
			if (posibl[j] == 0) { dirX = 1; dirY = 0; }
			else if (posibl[j] == 1) { dirX = 0; dirY = 1; }
			else if (posibl[j] == 2) { dirX = -1; dirY = 0; }
			else if (posibl[j] == 3) { dirX = 0; dirY = -1; }
			float numX = abs(gueim->PacManY() - (PosY+dirX));
			float numY = abs(gueim->PacManX() - (PosX+dirY));
			float distAux = sqrtf(powf(numX, 2) + powf(numY, 2));
			if (distAux < distancia)
			{
				distancia = distAux;
				dir = posibl[j];
			}
			j++;
		}
	}
}
//Comprueba las 4 posibles direcciones del Fantasma, descarta las inválidas y elige una de las posibles al azar

int SmartGhost::GetAnim()
{
	return anim;
}
//Devuelve la animacion actual del fantasma

void SmartGhost::Mueve(int fils, int cols)
{
	cout << "alog";
	CambiaDir();
	if (dir == 0)
	{
		PosY = (PosY + 1) % cols;
	}
	else if (dir == 1)
	{
		PosX = (PosX + 1) % fils;
	}
	else if (dir == 2)
	{
		if (PosY - 1 < 0) PosY = cols - 1;

		else PosY--;
	}
	else if (dir == 3)
	{
		if (PosX - 1 < 0) PosX = fils - 1;

		else PosX--;
	}
	if (anim == 1) anim = 0;
	else anim = 1;

}
//Mueve al fantasma en la direccion proporcionada por CambiaDir()

void SmartGhost::SetInicio() {
	PosX = IniX;
	PosY = IniY;
}
//Devuelve al fantasma a su posicion inicial

void SmartGhost::RenderGhost(SDL_Rect rekt, int d, PacMan* pacman)
{
	
	if (edad <= 20)
	{
		rekt.x += rekt.w / 2 -edad / 2;
		rekt.y += rekt.w / 2 - edad / 2;
		rekt.w = edad;
		rekt.h = edad;
	}
	if (pacman->Come)
	{
		text->RenderFrame(12, 0, rekt, render);
	}
	else
	{
		if (GetAnim() == 0)
			text->RenderFrame(d * 2, 0, rekt, render);
		else
			text->RenderFrame(d * 2 + 1, 0, rekt, render);
	}
	SumaEdad();
}
//Pinta al fantasma y lo anima en sus distintos casos

void SmartGhost::Render() {

}

void SmartGhost::update() {

}

bool SmartGhost::loadFromFile(string file) {
	return true;
}

bool SmartGhost::saveToFile(string file) {
	return true;
}

void SmartGhost::SumaEdad()
{
	edad += 0.5f;
}