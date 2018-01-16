#include "GameState.h"
#include"GameMap.h"


GameState::GameState()
{
	map = new GameMap(Fils, Cols, gueim->getRender());
	for (int i = 0; i < 4; i++)
		ghosts[i] = nullptr;
}

GameState::~GameState()
{
}

//Lee de archivo y crea un tablero con la información dada, igual que el antiguo de game
bool GameState::SetMap(string filename) {

	int aux = 0;
	//variable auxiliar para leer de archivo y asignar los distintos tipos de casillas

	ifstream archivo;

	archivo.open(filename);

	if (!archivo.fail()) {
		archivo >> Fils >> Cols;
		map = new GameMap(Fils, Cols, gueim->getRender());

		for (int i = 0; i < Fils; i++) {
			for (int j = 0; j < Cols; j++) {
				//recorremos la matriz entera

				archivo >> aux;
				//leemos el siguiente numero del archivo


				if (aux < 4)
				{
					map->SetCell(i, j, (MapCells)aux);
					//if (aux == 2) maxPunt++;
				}
				else if (aux <9) {
					map->SetCell(i, j, Vacio);
					ghosts[aux - 5] = new Ghost(i, j, gueim->getRender(), gueim);
				}
				else
				{
					map->SetCell(i, j, Vacio);
					pac = new PacMan(i, j,gueim->getRender(), gueim);
				}

			}
		}
		//maxComida = maxPunt;
	}
	int auxi = enemies.size();
	for (int i = 0; i < auxi; i++)
		enemies.pop_back();
	enemies.push_back(new SmartGhost(1, 1, gueim->getRender(), gueim));
	enemies.push_back(new SmartGhost(1, 3, gueim->getRender(), gueim));
	archivo.close();
	pac->RestartContador(50);
	return !archivo.fail();
}


//Comprueba las casillas del tablero, y llama al renderizado de cada una (al GameMap, al Pac-Man y a los Fantasmas)
void GameState::render() {
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

void GameState::Update() {
	if (map->tablero[pac->getPosY()][pac->getPosX()] == Comida)
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

void GameState::HandleEvent() {
	while (SDL_PollEvent(&evento))
	{
		if (evento.type == SDL_QUIT)
		{
			//exit = true;
		}
		else if (evento.type == SDL_KEYDOWN) {
			if (evento.key.keysym.sym == SDLK_UP)
			{
				pac->CambiaDir(3);
			}
			else if (evento.key.keysym.sym == SDLK_LEFT)
			{
				pac->CambiaDir(2);
			}
			else if (evento.key.keysym.sym == SDLK_DOWN)
			{
				pac->CambiaDir(1);
			}
			else if (evento.key.keysym.sym == SDLK_RIGHT)
			{
				pac->CambiaDir(0);
			}
			else if (evento.key.keysym.sym == SDLK_s)
			{
				//SaveToFile();
				//if (!pausa)pausa = true;
				//else pausa = false;

			}
		}
	}
}