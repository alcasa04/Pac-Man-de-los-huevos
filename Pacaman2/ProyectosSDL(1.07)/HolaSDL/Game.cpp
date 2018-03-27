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
#include"SDLError.h"
//Constructora de Game
Game::Game()
{
	stateMachine = new GameStateMachine();
	//inicializacion normal de la SDL
	//visto en los slides de clase
	int winX, winY;
	try
	{
		winX = winY = SDL_WINDOWPOS_CENTERED;
		if (winX == NULL || winY == NULL)
		{
			throw SDLError("Error checking center of SDL window");
		}
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
	catch (exception& e)
	{
		cout << e.what() << '\n';
	}
	newState(new MenuState(this));
}

//Carga la imagen del Menú
void Game::LoadTextures() {
	if (!menu->loadText("..\\images\\Pac-Titulo.png", 1, 2, render))error = true;
	//menu
}

//Hace que el Pac-Man se coma la comida y las vitaminas
void Game::Update()
{
	stateMachine->CurrentState()->update();
}

Game::~Game()
{

}


//Comprueba pulsaciones de teclado y actua conforme a ello
void Game::handleEvents() {
	while (SDL_PollEvent(&evento) && !stateMachine->empty())
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
	while (!exit && !stateMachine->empty()) {
		SDL_Delay(100);
		SDL_RenderClear(render);
		Update();
		stateMachine->CurrentState()->render();
		handleEvents();
		SDL_RenderPresent(render);
	}
}

//Muestra en consola la puntuación del modo: *Puntuación Actual/Puntuación Máxima*
void Game::GUI()
{
}

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

int Game::getFils()
{
	return Fils;
}
int Game::getCols()
{
	return Cols;
}

void Game::newState(GameState* newSt) {
	stateMachine->PushState(newSt);
}