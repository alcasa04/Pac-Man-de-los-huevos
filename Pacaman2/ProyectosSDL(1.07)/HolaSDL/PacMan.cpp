#include "PacMan.h"
#include"Game.h"
#include"GameMap.h"

#include"PlayState.h"

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
PacMan::PacMan(int x, int y, SDL_Renderer* rend, Game* game, PlayState* plai) : GameCharacter(x, y, game){
	play = plai;
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
	if (dir2 >= 0) {
		if (play->NextCell(PosX, PosY, dir2)) {
			//int nx = PosX, ny = PosY;
			if (dir2 == 0) {
				PosY++;
			}
			else if (dir2 == 2)
				PosY--;
			else if (dir2 == 1)
				PosX++;
			else PosX--;

			//toroide
			if (PosX >= fils)
				PosX = 0;
			else if (PosX < 0)
				PosX = fils - 1;
			else if (PosY >= cols)
				PosY = 0;
			else if (PosY < 0)
				PosY = cols;
			dir = dir2;
			dir2 = -1;
		}
		else {
			if (play->NextCell(PosX, PosY, dir)) {
				//int nx = PosX, ny = PosY;
				if (dir == 0) {
					PosY++;
				}
				else if (dir == 2)
					PosY--;
				else if (dir == 1)
					PosX++;
				else PosX--;

				//toroide
				if (PosX >= fils)
					PosX = 0;
				else if (PosX < 0)
					PosX = fils - 1;
				else if (PosY >= cols)
					PosY = 0;
				else if (PosY < 0)
					PosY = cols;
			}
		}
	}
	else {
		if (play->NextCell(PosX, PosY, dir)) {
			//int nx = PosX, ny = PosY;
			if (dir == 0) {
				PosY++;
			}
			else if (dir == 2)
				PosY--;
			else if (dir == 1)
				PosX++;
			else PosX--;

			//toroide
			if (PosX >= fils)
				PosX = 0;
			else if (PosX < 0)
				PosX = fils - 1;
			else if (PosY >= cols)
				PosY = 0;
			else if (PosY < 0)
				PosY = cols;
		}
		//cout << PosX << " " << PosY << endl;
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

void PacMan::RestartContador(int n)
{
	contador = n;
}
//Devuelve el contador a 0

void PacMan::RenderPac(SDL_Rect recta)
{
	//throw new PacManError("Error initializing the game");
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
bool PacMan::saveToFile(ofstream& archivo)
{
	archivo << IniX << " " << IniY << endl;
	archivo << PosX << " " << PosY << endl;
	archivo << contador << endl;

	return !archivo.fail();
}
bool PacMan::loadFromFile(ifstream& archivo)
{
	archivo >> IniX >> IniY;
	archivo >> PosX >> PosY;
	archivo >> contador;

	return !archivo.fail();

}