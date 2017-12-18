#include "PacMan.h"
#include"Game.h"
#include"GameMap.h"

PacMan::PacMan() : GameCharacter(0,0, nullptr){
	PosX = PosY = IniX = IniY = 0;
	//si no le pasamos parametros, asumiremos que PacMan esta en la posicion (0,0)
}
/*PacMan::PacMan(int x, int y,SDL_Renderer* rend, Game* game) : GameCharacter::GameCharacter(x, y, game) {
	PosX = x;
	PosY = y;
}
*/
//Constructora predeterminada
PacMan::PacMan(int x, int y, SDL_Renderer* rend, Game* game) : GameCharacter(x, y, game){
	PosX = IniX = x;
	PosY = IniY = y;
	dir = 0;
	render = rend;
	if (!text->loadText(("..\\images\\characters1.png"), 4, 14, render)) gueim->error = true;
	//le pasamos como parametros una x y una y, y situamos un PacMan en la posicion dada
}
//Constructora que coloca al Pac-Man

int PacMan::getPosX() {
	return PosX;
}
//Devuelve la X

int PacMan::getPosY() {
	return PosY;
}
//Devuelve la Y

int PacMan::GetDir()
{
	return dir;
}
//Devuelve la dirección actual

int PacMan::getTicks() {
	return numTicks;
}

void PacMan::CambiaEstado(int i)
{
	if (i == 0)
	{
		estado = DerCerrado;
	}
	else if (i == 1)
	{
		estado = DerAbierto;
	}
	else if (i == 2)
	{
		estado = BotCerrado;
	}
	else if (i == 3)
	{
		estado = BotAbierto;
	}
	else if (i == 4)
	{
		estado = IzqCerrado;
	}
	else if (i == 5)
	{
		estado = IzqAbierto;
	}
	else if (i == 6)
	{
		estado = TopCerrado;
	}
	else if (i == 7)
	{
		estado = TopAbierto;
	}
}
//Cambia la animación actual del Pac-Man

void PacMan::Mueve(int fils, int cols) 
{
	if ((dir2 == 0)&& gueim->NextCell(PosX, PosY,dir2))
	{
		PosY = (PosY + 1)%cols;
		dir = dir2;
		dir2 = -1;
		estado = DerCerrado;
	}
	else if ((dir2 == 1) && gueim->NextCell(PosX, PosY, dir2))
	{
		PosX = (PosX+1)%fils;
		dir = dir2;
		dir2 = -1;
		estado = BotCerrado;
	}
	else if ((dir2 == 2) && gueim->NextCell(PosX, PosY, dir2))
	{
		if (PosY - 1 < 0) PosY = cols - 1;

		else PosY--;
		dir = dir2;
		dir2 = -1;
		estado = IzqCerrado;
	}
	else if ((dir2 == 3) && gueim->NextCell(PosX, PosY, dir2))
	{
		if (PosX - 1 < 0) PosX = fils - 1;
		else PosX--;

		dir = dir2;
		dir2 = -1;
		estado = TopCerrado;
	}


	else if ((dir == 0) && gueim->NextCell(PosX, PosY, dir))
	{
		PosY = (PosY + 1)%cols;
	}
	else if ((dir == 1) && gueim->NextCell(PosX, PosY, dir))
	{
		PosX= (PosX + 1) % fils;
	}
	else if ((dir == 2) && gueim->NextCell(PosX, PosY, dir))
	{
		if (PosY - 1 < 0) PosY = cols - 1;

		else PosY--;
	}
	else if ((dir == 3) && gueim->NextCell(PosX, PosY, dir))
	{
		if (PosX - 1 < 0) PosX = fils - 1;

		else PosX--;
	}

}
//Mueve a Pac-Man en la nueva dirección proporcionada, o en la dirección anterior en su defecto

void PacMan::CambiaDir(int newdir)
{
	dir2 = newdir;
}
//Cambia la nueva direccion de Pac-Man

estadoPacMan PacMan::getEstado() {
	return estado;
}
//Devuelve la animación actual de Pac-Man

PacMan::~PacMan()
{
	delete text;
}
//Destructora de Pac-Man

void PacMan::Contador()
{
	if (Come)
	{
		if (contador <= 50)
		{
			contador++;
		}
		else
		{
			Come = false;
		}
	}
}
//Calcula el tiempo que esta Pac-Man en modo "COME"

void PacMan::RestartContador()
{
	contador = 0;
}
//Devuelve el contador a 0

void PacMan::RenderPac(SDL_Rect recta)
{
	int f = 0;
	bool acaba = false;
	while (f< 4 && !acaba)
	{
		if (dir == f)
		{
			if (estado == f * 2)
			{
				CambiaEstado(f * 2 + 1);
				text->RenderFrame(10, f, recta, render);
				acaba = true;
			}
			else
			{
				CambiaEstado(f * 2);
				text->RenderFrame(11, f, recta, render);
			}
		}
		f++;
	}
}
//Pinta a Pac-Man y a sus respectivas animaciones

void PacMan::Update() {  }
void PacMan::Render() {}
bool PacMan::saveToFile(string filename) { return true; }
bool PacMan::loadFromFile(string filename) { return true; }