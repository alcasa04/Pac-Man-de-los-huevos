#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include<iostream>
#include<fstream>
#include "Texture.h"
#include<vector>
//#include<list>

class GameCharacter;
class PacMan;
class Ghost;
class GameMap;
class SmartGhost;

using namespace std;

class Game 
{
private:

	//variables window de la SDL
	SDL_Window*window = nullptr;

	//variable render de la SDL
	SDL_Renderer* render = nullptr;

	//puntero a mapa del juego
	GameMap* map = nullptr;
	
	//puntero a pacman
	PacMan* pacman = nullptr;

	//list<GameCharacter*> lista;

	//array de punteros a fantasmas
	Ghost* ghosts[4];

	//si el juego esta pausado o no
	bool pausa = false;

	bool carga = false;
	//si es nueva partida o carga de partida guardada
	int estadoMenu = 1;
	//vector de enemigos
	vector<SmartGhost*> enemies;


	//vector de punteros a texturas
	vector<Texture*>texturas;

	//textura del menu
	Texture* menu = new Texture();
	
	//rectangulo destino, donde se pintara algo en pantalla
	SDL_Rect destRec;

	//para detectar eventos
	SDL_Event evento;

	//variable para controlar el final de la ventana
	bool exit = false;

	bool comienza = false;

	int menuAnim = 0;

	//dimensiones de la pantalla
	int WinWidth = 800;
	int WinHeight = 600;

	//filas y columnas del mapa
	int Fils = 0,
		Cols = 0;

	int puntos = 0,
		ActComida= 0,
		maxComida = 0;
	int maxPunt = 0;
	int Nivel =1 ;

	//numero de imagenes o texturas que se van a cargar
	const int numText = 4;

public:

	//variable para comprobar si ha habido un error en la carga de un archivo
	bool error = false;

	//constructora, inicializa todo
	Game();

	//destructora, deja todo a nullptr o lo destruye
	~Game();

	//carga un mapa de un fichero de texto dado
	bool SetMap(string filename);

	//carga todas las texturas (en este caso, 4)
	void LoadTextures();
	
	void GUI();

	void run();
	
	void Renderizado();
	
	void handleEvents();
	bool NextCell(int x, int y, int dir);
	void Update();
	void Colision();
	void finJuego();
	void Menu();
	void MenuEvents();
	int PacManX();
	int PacManY();

	bool SaveToFile();
	bool LoadFromFile();

	int getFils();
	int getCols();
	void creaFantasma(int posX, int posY);
	void CargaEvents();
};

