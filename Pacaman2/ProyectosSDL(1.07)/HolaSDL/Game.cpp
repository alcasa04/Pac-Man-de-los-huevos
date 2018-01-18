#include "Game.h"
#include"PacMan.h"
#include"GameMap.h"
#include"Ghost.h"
#include "SmartGhost.h"
#include"GameStateMachine.h"

#include"MenuState.h"
#include"PlayState.h"
#include"EndState.h"
#include"PauseState.h"
//Constructora de Game
Game::Game()
{
	//pacman = new PacMan();
	stateMachine = new GameStateMachine();
	//inicializacion normal de la SDL
	//visto en los slides de clase
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First text with SDL", winX, winY, WinWidth, WinHeight, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || render == nullptr)
		cout << "Error initializing SDL" << endl;


	else {
			string level;
			//aqui va el codigo que queremos ejecutar
			if (Nivel < 10) {
				level = "Level0" + to_string(Nivel) + ".dat";
			}
			else level = "Level" + to_string(Nivel) + ".dat";
			LoadTextures();
			//SetMap(level);
		}
}

//Lee de archivo y crea un tablero con la información dada
/*bool Game::SetMap(string filename) {

	int aux = 0;
	//variable auxiliar para leer de archivo y asignar los distintos tipos de casillas

	ifstream archivo;

	archivo.open(filename);

	if (!archivo.fail()) {
		archivo >> Fils >> Cols;
		map = new GameMap(Fils, Cols, render);

		for (int i = 0; i < Fils; i++) {
			for (int j = 0; j < Cols; j++) {
				//recorremos la matriz entera

				archivo >> aux;
				//leemos el siguiente numero del archivo


				if (aux < 4)
				{
					map->SetCell(i, j, (MapCells)aux);
					if (aux == 2) maxPunt++;
				}
				else if(aux <9){
					map->SetCell(i, j, Vacio);
					ghosts[aux - 5] = new Ghost(i, j, render, this);
				}
				else
				{
					map->SetCell(i, j, Vacio);
					pacman = new PacMan(i, j, render, this);
				}

			}
		}
		maxComida = maxPunt;
	}
	int auxi = enemies.size();
	for (int i = 0; i < auxi; i++)
		enemies.pop_back();
	enemies.push_back(new SmartGhost(1, 1, render, this));
	enemies.push_back(new SmartGhost(1, 3 ,render, this));
	archivo.close();
	pacman->RestartContador(50);
	return !archivo.fail();
}*/

//Carga la imagen del Menú
void Game::LoadTextures() {
	if (!menu->loadText("..\\images\\Pac-Titulo.png", 1, 2, render))error = true;
	//menu
}

//Comprueba las casillas del tablero, y llama al renderizado de cada una (al GameMap, al Pac-Man y a los Fantasmas)
/*void Game::Renderizado(){
	SDL_RenderClear(render);
	//const porque lo ponia en los slides 

	destRec.w = destRec.h = 20;
	//altura de la pantalla 600, numero de filas ~= 30, 600/30 = 20

	for (int j = 0; j < Fils; j++) 
	{

		destRec.y = j * 20 +((WinHeight - 20 * Cols) / 2);
		//vamos situando donde vamos a pintar (en este caso la fila)

		for (int i = 0; i < Cols; i++) 
		{
			//recorrido de la matriz entera

			destRec.x = (i * 20)+((WinWidth-20*Cols)/2);
			//asignamos en que columna se va a pintar

			if (map->tablero[i][j] == Muro) {
				map->Renderizado(destRec, 0);
			}
			//si es un muro, renderizamos la imagen del muro

			else if (map->tablero[i][j] == Comida) {
				map->Renderizado(destRec, 1);
			}
			//analogo para la comida

			else if (map->tablero[i][j] == Vitamina) {
				map->Renderizado(destRec, 2);
			}
			//analogo para la vitamina



			for (int d = 0; d < 4; d++)
			{
				if ((ghosts[d]->getPosX() == j) && (ghosts[d]->getPosY() == i))
				{
					ghosts[d]->RenderGhost(destRec, d, pacman);
				}
				//si no es ninguna de las anteriores, es una casilla vacia, de modo
				//que comprobamos si es la posicion del fantasma 1 y si lo es lo pintamos
			}
			//Renderizado de fantasmas

			if (pacman->getPosX() == j && pacman->getPosY() == i)
			{ 
				pacman->RenderPac(destRec);
			}
			for (int a = 0; a < enemies.size(); a++)
			{
				if (enemies[a]->getPosX() == j && enemies[a]->getPosY() == i) enemies[a]->RenderGhost(destRec, pacman);
			}
			//Renderizado de PacMan
		}
	}
	SDL_RenderPresent(render);
	//pintamos la escena
}*/

//Hace que el Pac-Man se coma la comida y las vitaminas
void Game::Update()
{
	stateMachine->CurrentState()->Update();
}

//Comprueba si tu puntuación es igual a la puntuación máxima
/*void Game::finJuego()
{
	if (ActComida >= maxComida)
	{
		Nivel++;
		if (Nivel < 10) {
			string level = "Level0" + to_string(Nivel) + ".dat";
			SetMap(level);
		}
		else
		{
			string level = "Level" + to_string(Nivel) + ".dat";
			SetMap(level);
		}
	}
}*/

//Comprueba el choque entre Pac-Man y los Fantasmas
/*void Game::Colision()
{
	for (int i = 0; i < 4; i++)
	{

		if (pacman->getPosX() == ghosts[i]->getPosX() && pacman->getPosY() == ghosts[i]->getPosY() && pacman->Come == false)
		{
			exit = true;
		}
		else if (pacman->getPosX() == ghosts[i]->getPosX() && pacman->getPosY() == ghosts[i]->getPosY() && pacman->Come == true)
		{
			ghosts[i]->SetInicio();
			puntos += 10;
		}

	}
	for(int i = 0; i < enemies.size(); i++)
    {
		if (pacman->getPosX() == enemies[i]->getPosX() && pacman->getPosY() == enemies[i]->getPosY() && pacman->Come == false && !enemies[i]->estaMuerto())
		{
			exit = true;
		}
		else if(pacman->getPosX() == enemies[i]->getPosX() && pacman->getPosY() == enemies[i]->getPosY() && (pacman->Come == true || enemies[i]->estaMuerto()))
		{
			if (!enemies[i]->estaMuerto()) {
				enemies[i]->SetInicio();
				puntos += 15;
			}
		}
		for (int j = 0; j < enemies.size(); j++)
		{
			if (i != j && enemies[i]->getPosX() == enemies[j]->getPosX() && enemies[i]->getPosY() == enemies[j]->getPosY() &&
				enemies[i]->esAdulto() && enemies[j]->esAdulto() && enemies[i]->esPadre() == false && enemies[j]->esPadre() == false)
			{
				
				creaFantasma(enemies[i]->getPosX(), enemies[i]->getPosY());
				enemies[i]->CambiaPapa();
				enemies[j]->CambiaPapa();
			}
		}
	}
}*/

//Destructora de Game
Game::~Game()
{
	/*for (int i = 0; i < 4; i++)
	{
		//delete ghosts[i];
	}
	delete pacman;
	SDL_DestroyRenderer(render);
	delete map;
	delete menu;
	for (int i = 0; i < enemies.size(); i++) {
		delete enemies[i];
	}

	//destruimos todo
	*/
}


//Comprueba pulsaciones de teclado y actua conforme a ello
void Game::handleEvents() {
	while (SDL_PollEvent(&evento))
	{
		if (evento.type == SDL_QUIT)
		{
			exit = true;
		}
		else {
			stateMachine->CurrentState()->HandleEvent(evento);
		}
	}
}

//Realiza los bucles principales del juego (Menu y juego), realizando sus correspondientes llamadas
void Game::run()
{
	stateMachine->PushState(new MenuState(this));
	while (!exit && !stateMachine->empty()) {
		//if (!pausa)
		//{
		SDL_Delay(50);
		//stateMachine->CurrentState()->HandleEvent();
		Update();
		stateMachine->CurrentState()->render();
		//GUI();
		//}
		//else
		//{
		handleEvents();
			//SDL_Delay(50);
		//}
		//handleEvents();
	}
	if (exit)
		cout << "Perdiste!" << endl;
	else
	{
		cout << "Ganaste!" << endl;

	}
	exit = true;
	//stateMachine->CurrentState()->render();
	//SDL_Delay(2000);
}

//Muestra en consola la puntuación del modo: *Puntuación Actual/Puntuación Máxima*
void Game::GUI()
{
	//stateMachine->CurrentState();
}

//Comprueba si la casilla destino está disponible para desplazarse
/*bool Game::NextCell(int y, int x, int dir)
{
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


		else if (dir == 0 && map->tablero[x + 1][y] == Muro)
			return false;
		else if (dir == 1 && map->tablero[x][y + 1] == Muro)
			return false;
		else if (dir == 2 && map->tablero[x - 1][y] == Muro)
			return false;
		else if (dir == 3 && map->tablero[x][y - 1] == Muro)
			return false;
		else return true;
	
}*/

//Animacion del menu
void Game::Menu()
{   
	destRec.w = 300;
	destRec.h = 500;
	destRec.y = 70;
	destRec.x = 250;
	menu->RenderFrame(menuAnim, 0, destRec, render);
	SDL_RenderPresent(render);
	menuAnim++;
	if (menuAnim == 2) menuAnim = 0;
}

//Pulsación de Espacio en el menu
void Game::MenuEvents()
{

	while (SDL_PollEvent(&evento))
	{
		if (evento.type == SDL_QUIT)
		{
			exit = true;
		}
		/*
		else if (evento.type == SDL_KEYDOWN) {
			if(evento.key.keysym.sym == SDLK_SPACE)
			{
				comienza = true;
			}
			if (evento.key.keysym.sym == SDLK_c)
			{
				carga = true;
				comienza = true;
			}
		}
		*/
		else if (evento.type == SDL_MOUSEBUTTONDOWN)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (x > WinWidth / 2 - 100 && x < WinWidth / 2 + 100 && y > WinHeight / 2 + 175 && y < WinHeight / 2 + 205)
			{
				comienza = true;
			}
			else if (x > WinWidth / 2 - 100 && x < WinWidth / 2 + 100 && y > WinHeight / 2 + 220 && y < WinHeight / 2 + 250)
			{
				comienza = true;
				carga = true;
			}
			
		}
	}
}

/*int Game::PacManX()
{
	return(pacman->getPosX());
}
int Game::PacManY()
{
	return(pacman->getPosY());
}*/

/*bool Game::SaveToFile() {
	//lectura en pantalla y pausa del juego
	string entrada;
	cin >> entrada;
	//if (entrada == " ")//de momento solo un espacio
	//{
		ofstream archivo;
		archivo.open("Save.txt");
		archivo << entrada << endl;
		archivo << puntos <<" "<< ActComida <<" "<< maxComida<< endl;
		if (!map->saveToFile(archivo))error = true;
		//if (!pacman->saveToFile(archivo))error = true;

		for (int i = 0; i < 4; i ++ ) {
			if (!ghosts[i]->saveToFile(archivo))error = true;
		}

		archivo << enemies.size() << endl;
		for (int i = 0; i < enemies.size(); i++) {
			if (!enemies[i]->saveToFile(archivo))error = true;
		}
		/*
		for (int i = 0; i < lista.size(); i++)
			if (!lista[i]->saveToFile(archivo))error = true;
			
		//iterator* i = new iterator();
		//quedan los fantasmas

		archivo.close();
		return archivo.fail();
	//}
}*/

/*bool Game::LoadFromFile() {
	int aux = enemies.size();
	for (int i = 0; i < aux; i++)
		enemies.pop_back();
	string entrada, code;
	ifstream archivo;
	cin >> entrada;
	archivo.open("Save.txt");
	archivo >> code;
	if (entrada == code) {
		archivo >> puntos >> ActComida >> maxComida;
		map = new GameMap(0, 0, render);
		if (!map->loadFromFile(archivo))error = true;

		//pacman = new PacMan(0, 0, render, this);
		//if (!pacman->loadFromFile(archivo))error = true;

		for (int i = 0; i < 4; i++) {
			ghosts[i] = new Ghost(0, 0, render, this);
			if (!ghosts[i]->loadFromFile(archivo))error = true;
		}
		int numEnemies = 0;
		archivo >> numEnemies;
		for (int i = 0; i < numEnemies; i++) {
			enemies.push_back(new SmartGhost(0, 0, render, this));
			if (!enemies[i]->loadFromFile(archivo))error = true;
		}
		
		int aux = 0;
		archivo >> aux;
		for (int i = 0; i < aux; i++) {
			lista.push_back(new GameCharacter(0, 0, this));

		}
	}
	archivo.close();
	return !archivo.fail();
}*/

int Game::getFils()
{
	return Fils;
}
int Game::getCols()
{
	return Cols;
}
/*void Game::creaFantasma(int posX, int posY)
{

	int contador = 0;
	vector<int>posibles;
	int dir;
	for (int i = 0; i < 4; i++)
	{
		if (NextCell(posX, posY, i))
		{
			contador++;
			posibles.push_back(i);
		}
	}
	if (contador > 0)
	{
		int random = rand() % contador;
		if (posibles[random] == 0) posY++;
		else if (posibles[random] == 1)posX++;
		else if (posibles[random] == 2)posY--;
		else if (posibles[random] == 3)posX--;
		enemies.push_back(new SmartGhost(posX, posY, render, this));
	}
}*/



void Game::newState(GameState* newSt) {
	stateMachine->PushState(newSt);
}