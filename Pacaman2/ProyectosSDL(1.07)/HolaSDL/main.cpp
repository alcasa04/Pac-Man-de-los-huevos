#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include"Game.h"
#include "PacManError.h"

using namespace std;

int main(int argc, char* argv[]){
	try {
		Game* game = new Game();
		game->run();
		SDL_Quit();
		delete game;
	}
	catch(int e)
	{
		throw new PacManError("Error initializing the game");
	}
	
	return 0;
}
//Metodo principal, que corre el juego y lo destruye al acabar