#include "Ghost.h"
#include"Game.h"
#include"GameMap.h"

Ghost::Ghost() : GameCharacter(0,0, nullptr){
	IniX = IniY = PosX = PosY = 0;
}
//constructora default que deja el fantasma en la posicion (0,0)

Ghost::Ghost(int x, int y, SDL_Renderer* rend, Game* game) : GameCharacter(x, y, game)
{
	PosX = IniX = x;
	PosY = IniY = y;
	dir = 0;
	render = rend;
	if (!text->loadText(("..\\images\\characters1.png"), 4, 14, render)) gueim->error = true;
}
//Constructora que situa al fantasma en una posicion dada

int Ghost::getPosX() {
	return PosX;
}
//Devuelve su X

int Ghost::getPosY() {
	return PosY;
}
//Devuelve su Y

Ghost::~Ghost()
{
	delete text;
}
//Destructora de Ghost

void Ghost::CambiaDir()
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
	else if(contador == 0)
	{
		dir = (dir + 2) % 4;
	}
}
//Comprueba las 4 posibles direcciones del Fantasma, descarta las inválidas y elige una de las posibles al azar

int Ghost::GetAnim()
{
	return anim;
}
//Devuelve la animacion actual del fantasma

void Ghost::Mueve(int fils, int cols)
{

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

void Ghost::SetInicio(){
	PosX = IniX;
	PosY = IniY;
}
//Devuelve al fantasma a su posicion inicial

void Ghost::RenderGhost(SDL_Rect rekt, int d, PacMan* pacman)
{
	
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
}
//Pinta al fantasma y lo anima en sus distintos casos

void Ghost::Render() {

}

void Ghost::update() {

}

bool Ghost::loadFromFile(string file) {
	return true;
}

bool Ghost::saveToFile(string file) {
	return true;
}