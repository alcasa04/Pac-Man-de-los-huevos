#include "PlayState.h"
#include"GameMap.h"
#include"GameStateMachine.h"

#include"PauseState.h"
#include"EndState.h"
#include"MenuState.h"

//constructora y destructora
PlayState::PlayState():GameState()
{

}

PlayState::~PlayState()
{
}

//metodos virtuales heredados
void PlayState::Update() {
	if (map->getTablero()[pac->getPosY()][pac->getPosX()] == Comida)
	{
		map->SetCell(pac->getPosX(), pac->getPosY(), Vacio);
		//puntos++;
		//ActComida++;
	}
	else if (map->getTablero()[pac->getPosY()][pac->getPosX()] == Vitamina)
	{
		pac->Come = true;
		pac->RestartContador(0);
		map->SetCell(pac->getPosX(), pac->getPosY(), Vacio);
	}
}

void PlayState::render() {
	SDL_RenderClear(gueim->getRender());
	//const porque lo ponia en los slides 

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

			if (map->getTablero()[i][j] == Muro) {
				map->Renderizado(destRec, 0);
			}
			//si es un muro, renderizamos la imagen del muro

			else if (map->getTablero()[i][j] == Comida) {
				map->Renderizado(destRec, 1);
			}
			//analogo para la comida

			else if (map->getTablero()[i][j] == Vitamina) {
				map->Renderizado(destRec, 2);
			}
			//analogo para la vitamina



			for (int d = 0; d < 4; d++)
			{
				if ((ghosts[d]->getPosX() == j) && (ghosts[d]->getPosY() == i))
				{
					ghosts[d]->RenderGhost(destRec, d, pac);
				}
				//si no es ninguna de las anteriores, es una casilla vacia, de modo
				//que comprobamos si es la posicion del fantasma 1 y si lo es lo pintamos
			}
			//Renderizado de fantasmas

			if (pac->getPosX() == j && pac->getPosY() == i)
			{
				pac->RenderPac(destRec);
			}
			for (int a = 0; a < enemies.size(); a++)
			{
				if (enemies[a]->getPosX() == j && enemies[a]->getPosY() == i) enemies[a]->RenderGhost(destRec, pac);
			}
			//Renderizado de PacMan
		}
	}
	SDL_RenderPresent(gueim->getRender());
	//pintamos la escena
}

void PlayState::HandleEvents(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.type == SDLK_ESCAPE) {
			gueim->newState(new PauseState());
		}
	}
}

//metodos propios
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

void PlayState::FinJuego() {
	if (ActComida >= MaxComida) {
		nivel++;
		if (nivel < 10) {
			string level = "level0" + to_string(nivel) + ".dat";
			SetMap(level);
		}
		else {
			string level = "level"+to_string(nivel) + ".dat";
			SetMap(level);
		}
	}
}

void PlayState::Colision() {
	//colision con fantasmas normales
	for (int i = 0; i < 4; i++) 
	{
		if (pac->getPosX() == ghosts[i]->getPosX() && pac->getPosY() == ghosts[i]->getPosY())
		{
			if (pac->Come) 
			{
				ghosts[i]->SetInicio();
				puntos += 10;
			}
			else 
			{
				gueim->newState(new EndState());											//provisional, hay que pasarle new EndState o algo
			}
		}
	}
	//colision con fantasmas inteligentes
	for (int i = 0; i < enemies.size(); i++) 
	{
		if (pac->getPosX() == enemies[i]->getPosX() && pac->getPosY() == enemies[i]->getPosY()) 
		{
			if (pac->Come) {
				enemies[i]->SetInicio();
				puntos += 15;
			}
			else {
				gueim->newState(new EndState());											//provisional, hay que pasarle new EndState o algo
			}
		}
		//colision con otros fantasmas inteligente para reproduccion
		for (int j = 0; j < enemies.size(); j++)
		{
			if (i != j && enemies[i]->getPosX() == enemies[j]->getPosX() && enemies[i]->getPosY() == enemies[j]->getPosY() &&
				enemies[i]->esAdulto() && enemies[j]->esAdulto() && !enemies[i]->esPadre() && !enemies[j]->esPadre()) 
			{
				CreaFantasma(enemies[i]->getPosX(), enemies[i]->getPosY());
				enemies[i]->CambiaPapa();
				enemies[j]->CambiaPapa();
			}
		}
	}
}

void PlayState::CreaFantasma(int x, int y) {
	int contador = 0;
	vector<int>posibles;
	int dir;
	//analiza las 4 casillas colindantes y halla las que no sean muros
	for (int i = 0; i < 4; i++) {
		if (NextCell(x, y, i)) {
			contador++;
			posibles.push_back(i);
		}
	}
	//si hemos encontrado una casilla libre
	if (contador > 0) {
		int random = rand() % contador;
		if (random == 0)y++;
		else if (random == 1)x++;
		else if (random == 2)y--;
		else x--;
		enemies.push_back(new SmartGhost(x, y, gueim->getRender(), gueim));		//cambiar de game a playstate en la constructora tambien
	}
}
