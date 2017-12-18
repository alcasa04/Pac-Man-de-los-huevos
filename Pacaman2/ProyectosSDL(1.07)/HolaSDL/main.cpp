#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include"Game.h"

using namespace std;

int main(int argc, char* argv[]){
	Game* game = new Game();
	game->run();
	SDL_Quit();
	game->~Game();
	
	return 0;
}
//Metodo principal, que corre el juego y lo destruye al acabar