#include "Texture.h"
//inlcusiones circulares, romper el ciclo e include el.h de uno en el cpp del otro
using namespace std;

Texture::Texture()
{
	//constructora dificil
}

bool Texture::loadText(const string filename,int numRows, int numCols, SDL_Renderer* render) 
{
	this->numRows = numRows;
	this->numCols = numCols;
	//this apunta a texture.h
		
	SDL_Surface* surface = IMG_Load(filename.c_str());	
	//surface con el string que pase el user

	if (surface != nullptr) {
		//Si no ha habido un error al cargar la surface

		free();
		//destruimos por si hay una textura anterior (prevencion de errores)

		texture = SDL_CreateTextureFromSurface(render, surface);	
		//textura con la surface anterior

		if (texture != nullptr) {
			//si no ha habido un error al cargar la textura

			w = surface->w;
			h = surface->h;

			fw = w / numCols;
			fh = h / numRows;
			//variables para el numero de frames

			//asignamos las variables necesarias
		}

		return texture != nullptr;
		//si es igual es que ha habido un error en la carga
	}
	else
		//si falla la carga de surface devolvemos false indicando que ha habido un error
		return false;
	
}
//Carga una imagen

void Texture::free() {

	SDL_DestroyTexture(texture);

	texture = nullptr;
	//lo dejamos vacio

	w = h = 0;
	//reseteo de variables
}
//Destruye una textura

void Texture::Render(SDL_Rect& dest, SDL_Renderer* render) {

	srcRect.x = srcRect.y = 0;
	//para coger la imagen entera

	srcRect.h = h;
	srcRect.w = w;
	//asignamos los valores del srcRect a los que queremos

	SDL_RenderCopy(render, texture, &srcRect, &dest);
	//copiamos la textura para renderizarla
}
//Pinta una imagen en un rectangulo destino y en unas cordenadas

void Texture::RenderFrame(const int x, const int y, SDL_Rect& dest, SDL_Renderer* render) {
	srcRect.x = x*fw;
	srcRect.y = y*fh;
	srcRect.w = fw;
	srcRect.h = fh;
	//asignamos los valores a los deseados
	SDL_RenderCopy(render, texture, &srcRect, &dest);
	//copiamos para poder renderizar posteriormente
}
//Pinta una imagen, dividida por frames