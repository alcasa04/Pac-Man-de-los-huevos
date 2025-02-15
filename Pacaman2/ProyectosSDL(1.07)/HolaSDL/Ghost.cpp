#include "Ghost.h"
#include"Game.h"
#include"GameMap.h"

#include"PlayState.h"

Ghost::Ghost() : GameCharacter(0,0, nullptr){
	IniX = IniY = PosX = PosY = 0;
}
//constructora default que deja el fantasma en la posicion (0,0)

Ghost::Ghost(int x, int y, SDL_Renderer* rend, Game* game, PlayState* plai, PacMan* pacman, int fantasma) : GameCharacter(x, y, game)
{
	play = plai;
	PosX = IniX = x;
	PosY = IniY = y;
	dir = 0;
	render = rend;
	if (!text->loadText(("..\\images\\characters1.png"), 4, 14, render)) gueim->error = true;
	rect.w = rect.h = 20;
	pac = pacman;
	d = fantasma;
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
		if (play->NextCell(PosX, PosY, i) && i != (dir + 2) % 4)
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

void Ghost::RenderGhost(int d, PacMan* pacman)
{
	rect.x = (PosY+6) * 20;
	rect.y = (PosX+1) * 20;
	if (pacman->Come)
	{
		text->RenderFrame(12, 0, rect, render);
	}
	else
	{
		if (GetAnim() == 0)
			text->RenderFrame(d * 2, 0, rect, render);
		else
			text->RenderFrame(d * 2 + 0, 0, rect, render);
	}
}
//Pinta al fantasma y lo anima en sus distintos casos

void Ghost::Render() {
	RenderGhost(d, pac);
}

void Ghost::update() {
	Mueve(play->getFils(), play->getCols());
}

bool Ghost::loadFromFile(ifstream& archivo) {
	archivo >> IniX >> IniY;
	if (IniX < 0 || IniY < 0)
		return false;
	archivo >> PosX >> PosY;
	if (IniX < 0 || IniY < 0)
		return false;

	return !archivo.fail();
}

bool Ghost::saveToFile(ofstream& archivo) {
	archivo << IniX << " " << IniY << endl;
	archivo << PosX << " " << PosY << endl;

	return !archivo.fail();
}