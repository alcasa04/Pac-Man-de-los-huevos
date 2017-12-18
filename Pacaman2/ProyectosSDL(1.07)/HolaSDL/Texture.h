#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include<iostream>
#include<string>

using namespace std;
//class Game; problema de inclusiones circulares
class Texture
{
	
public:
	bool loadText(const string filename, int numRows, int numCols, SDL_Renderer* render);
	/*metodo que carga una textura, 
	devuelve true si se ha cargado con exito y false si ha habido un error*/

	Texture();
	//constructora

	~Texture()
	{
		free();
	};
	//llama al metodo free() para destruir la textura

	void free();
	/*metodo que destruye una textura
	y resetea las variables*/

	void Render(SDL_Rect& destRect, SDL_Renderer* renderer);
	/*metodo que pinta en una ubicacion dada (rectangulo destino)
	la imagen con todos los frames de la textura*/

	void RenderFrame(const int x, const int y, SDL_Rect& destRect, SDL_Renderer* renderer);
	/*metodo que pinta un frame determinado dadas una x y una y
	(en el source rect) y lo situa en un rectagulo tambien
	dado (destRect)*/

private:

	SDL_Texture* texture = nullptr;
	//SDL_Renderer* render = nullptr;
	//Inicializamos las texturas y el render a nullptr

	SDL_Rect srcRect;
	//sourceRect, que frame se pintara

	uint16_t w = 0,
		h = 0,
		//dimensiones de la imagen

		fw = 0,	
		//frame width

		fh = 0,	
		//frame height

		numRows = 1,
		numCols = 1;
		//numero de columnas y de filas de la imagen
};