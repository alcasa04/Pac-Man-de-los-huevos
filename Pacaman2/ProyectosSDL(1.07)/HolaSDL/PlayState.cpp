#include "PlayState.h"
#include"GameMap.h"
#include"GameState.h"


PlayState::PlayState():GameState()
{

}


PlayState::~PlayState()
{
}

void PlayState::Update() {

}

void PlayState::render() {
	
}

void PlayState::HandleEvents(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.type == SDLK_ESCAPE) {
			//gueim->getMachine()->
		}
	}
}

bool PlayState::NextCell(int x, int y, int dir) {
	//Si se sale de pantalla hace recursión de NextCell en la posición contraria
	if (dir == 0 && x + 1 >= Cols)
	{
		if (NextCell(y, -1, 0))
			return true;
	}
	//Same
	else if (dir == 2 && x - 1 < 0)
	{
		if (NextCell(y, Cols, 2))
			return true;
	}
	//Same
	else if (dir == 1 && y + 1 >= Fils)
	{
		if (NextCell(-1, x, 1))
			return true;
	}
	//Same
	else if (dir == 3 && y - 1 < 0)
	{
		if (NextCell(Fils, x, 3))
			return true;
	}

	
	else if (dir == 0 && map->getTablero()[x + 1][y] == Muro)
		return false;
	else if (dir == 1 && map->getTablero()[x][y + 1] == Muro)
		return false;
	else if (dir == 2 && map->getTablero()[x - 1][y] == Muro)
		return false;
	else if (dir == 3 && map->getTablero()[x][y - 1] == Muro)
		return false;
	else return true;

}

bool PlayState::SaveToFile() {
	//lectura en pantalla y pausa del juego
	string entrada;
	cin >> entrada;
	//if (entrada == " ")//de momento solo un espacio
	//{
	ofstream archivo;
	archivo.open("Save.txt");
	archivo << entrada << endl;
	//archivo << puntos << " " << ActComida << " " << maxComida << endl;
	if (!map->saveToFile(archivo))gueim->error = true;
	if (!pac->saveToFile(archivo))gueim->error = true;

	for (int i = 0; i < 4; i++) {
		if (!ghosts[i]->saveToFile(archivo))gueim->error = true;
	}
	archivo << enemies.size() << endl;
	for (int i = 0; i < enemies.size(); i++) {
		if (!enemies[i]->saveToFile(archivo))gueim->error = true;
	}
	/*
	for (int i = 0; i < lista.size(); i++)
	if (!lista[i]->saveToFile(archivo))error = true;
	*/
	//iterator* i = new iterator();
	//quedan los fantasmas

	archivo.close();
	return archivo.fail();
}
