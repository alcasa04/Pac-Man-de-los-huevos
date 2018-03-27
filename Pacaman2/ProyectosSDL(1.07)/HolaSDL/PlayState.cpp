#include "PlayState.h"
#include"GameMap.h"
#include"GameStateMachine.h"
#include"PauseState.h"
#include"EndState.h"
#include"MenuState.h"
#include"FileFormatError.h"

//constructora y destructora
PlayState::PlayState(Game* game):GameState(game)
{
	string level;
	//aqui va el codigo que queremos ejecutar
	if (Nivel < 10) {
		level = "Level0" + to_string(Nivel) + ".dat";
	}
	else level = "Level" + to_string(Nivel) + ".dat";
	//LoadTextures();
	SetMap(level);
}

PlayState::~PlayState()
{
}

PlayState::PlayState(Game* game, int qwert) :GameState(game)
{
	rend = game->getRender();
		string entrada, code;
		ifstream archivo;
	try{
		cin >> entrada;
		archivo.open("Save.txt");
		if (archivo.fail()) {
			throw FileFormatError("Couldnt find any saved game, going back to menu");
		}
		archivo >> code;
		if (code == "") {
			throw FileFormatError("There wasnt any game saved, so it's impossible to load any game");
		}
		if (entrada == code) {
			archivo >> puntos >> ActComida >> MaxComida;
			if (MaxComida < ActComida || MaxComida < 0) {
				throw FileFormatError("Error reading data from save file, posible negative number");
			}
			map = new GameMap(0, 0, gueim->getRender(), this);
			if (!map->loadFromFile(archivo))
				throw FileFormatError("Error while reading the data from the map");
			Fils = map->getFils();
			Cols = map->getCOls();

			pac = new PacMan(0, 0, gueim->getRender(), gueim, this);
			objetos.push_back(pac);
			if (!pac->loadFromFile(archivo))
				throw FileFormatError("Error while reading the data from the pacman");
			for (int i = 0; i < 4; i++) {

				ghosts.push_back(new Ghost(0, 0, gueim->getRender(), gueim, this, pac, i));
				objetos.push_back(ghosts[i]);
				if (!ghosts[i]->loadFromFile(archivo))
					throw FileFormatError("Error while reading the data from common ghosts");
			}
			int numEnemies = 0;
			archivo >> numEnemies;
			for (int i = 0; i < numEnemies; i++) {
				enemies.push_back(new SmartGhost(0, 0, gueim->getRender(), gueim, this, pac));
				objetos.push_back(enemies[i]);
				if (!enemies[i]->loadFromFile(archivo))
					throw FileFormatError("Error while reading the data from smartghosts");
			}
		}
		archivo.close();
	}
	catch(exception &e) {
		archivo.close();
		cout << e.what() << '\n';
		gueim->getMachine()->PopState();
	}
}

//metodos virtuales heredados
void PlayState::Update() {

	GameState::update();
	map->AnimVit();
	FinJuego();
	GUI();
}

void PlayState::render() {

	GameState::render();
}

void PlayState::HandleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			gueim->newState(new PauseState(gueim));
		}
		else if (e.key.keysym.sym == SDLK_UP)
				{
					pac->CambiaDir(3);
				}
		else if (e.key.keysym.sym == SDLK_LEFT)
				{
					pac->CambiaDir(2);
				}
		else if (e.key.keysym.sym == SDLK_DOWN)
				{
					pac->CambiaDir(1);
				}
		else if (e.key.keysym.sym == SDLK_RIGHT)
				{
					pac->CambiaDir(0);
				}
		}
}

//metodos propios
bool PlayState::NextCell(int x, int y, int dir) {
	int nx=x, ny=y;
	if (dir == 0) {
		ny++;
	}
	else if (dir == 2)
		ny--;
	else if (dir == 1)
		nx++;
	else nx--;

	if (nx >= Fils)
		nx = 0;
	else if (nx < 0)
		nx = Fils - 1;
	else if (ny >= Cols)
		ny = 0;
	else if (ny < 0)
		ny = Cols;

	return map->getTablero()[nx][ny] != Muro;

	
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
	archivo << puntos << " " << ActComida <<" "<< MaxComida<< endl;
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

	archivo.close();
	return archivo.fail();
}

void PlayState::FinJuego() {
	if (ActComida >= MaxComida) {
		Nivel++;
		if (Nivel < 10) {
			string level = "level0" + to_string(Nivel) + ".dat";
			SetMap(level);
		}
		else {
			string level = "level"+to_string(Nivel) + ".dat";
			SetMap(level);
		}
	}
}

void PlayState::Colision() {

	//colision con fantasmas normales
	for (int i = 0; i < 4; i++) 
	{
		if (pac->getPosX() == ghosts[i]->getPosX() && pac->getPosY() == ghosts[i]->getPosY() && !collision)
		{
			if (pac->Come) 
			{
				ghosts[i]->SetInicio();
				puntos += 10;
			}
			else 
			{
				gueim->newState(new EndState(gueim));
				collision = true;
			}
		}
	}
	//colision con fantasmas inteligentes
	for (int i = 0; i < enemies.size(); i++) 
	{
		if (pac->getPosX() == enemies[i]->getPosX() && pac->getPosY() == enemies[i]->getPosY() && !collision) 
		{
			if (pac->Come) {
				enemies[i]->SetInicio();
				puntos += 15;
			}
			else {
				collision = true;
				gueim->newState(new EndState(gueim));											//provisional, hay que pasarle new EndState o algo
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
	if (map->getTablero()[pac->getPosX()][pac->getPosY()] == Comida)
	{
		map->SetCell(pac->getPosX(), pac->getPosY(), Vacio);
		puntos++;
		ActComida++;
	}
	else if (map->getTablero()[pac->getPosX()][pac->getPosY()] == Vitamina)
	{
		pac->Come = true;
		pac->RestartContador(0);
		map->SetCell(pac->getPosX(), pac->getPosY(), Vacio);
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
		enemies.push_back(new SmartGhost(x, y, gueim->getRender(), gueim, this, pac));		//cambiar de game a playstate en la constructora tambien
	}
}

struct fant
{
	int posX;
	int posY;
	int anim;
};
//Lee de archivo y crea un tablero con la información dada, igual que el antiguo de game
bool PlayState::SetMap(string filename) {

	int aux = 0;
	int aux2 = 0;
	vector<fant*> fantasma;
	//variable auxiliar para leer de archivo y asignar los distintos tipos de casillas

	ifstream archivo;

	archivo.open(filename);

	if (!archivo.fail()) {
		archivo >> Fils >> Cols;
		map = new GameMap(Fils, Cols, gueim->getRender(), this);
		objetos.push_back(map);
		for (int i = 0; i < Fils; i++) {
			for (int j = 0; j < Cols; j++) {
				//recorremos la matriz entera

				archivo >> aux;
				//leemos el siguiente numero del archivo
				if (aux == 9)
				{
					map->SetCell(i, j, Vacio);
					pac = new PacMan(i, j, gueim->getRender(), gueim, this);
					objetos.push_back(pac);
				}
				else if (aux < 4)
				{
					map->SetCell(i, j, (MapCells)aux);
					if (aux == 2) maxPunt++;
				}
				else if (aux <9) {
					aux2++;
					map->SetCell(i, j, Vacio);
					fant* fantas = new fant();
					fantas->posX = i;
					fantas->posY = j;
					fantas->anim = aux2;
					fantasma.push_back(fantas);
				}
			}
		}
		MaxComida = maxPunt;
	}
	for (int i = 0; i < fantasma.size(); i++)
	{
		ghosts.push_back(new Ghost(fantasma[i]->posX, fantasma[i]->posY, gueim->getRender(), gueim, this, pac, fantasma[i]->anim));
		objetos.push_back(ghosts[i]);
	}
	int auxi = enemies.size();
	for (int i = 0; i < auxi; i++)
		enemies.pop_back();
	enemies.push_back(new SmartGhost(1, 1, gueim->getRender(), gueim,this, pac));
	enemies.push_back(new SmartGhost(1, 3, gueim->getRender(), gueim, this, pac));
	for (int i = 0; i < enemies.size(); i++)
	{
		objetos.push_back(enemies[i]);
	}
	archivo.close();
	pac->RestartContador(50);
	return !archivo.fail();
}

void PlayState::GUI() {
	system("cls");
	cout << "puntos: " << puntos << endl;
}
