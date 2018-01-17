#pragma once
#include"GameCharacter.h"

class Game;

class SmartGhost : public GameCharacter
{
private:

	//posiciones actuales e iniciales del fantasma

	int anim = 0;
	float edad = 5;
	bool padre = false;
	bool muerto = false;

	//Game* game = nullptr;


	/*
		 /\
		 |
		 3
	<--2 X	0-->
		 1
		 |
		 \/
	*/

public:
	SmartGhost();
	//constructora default, situa fantasma en (0,0)

	SmartGhost(int x, int y, SDL_Renderer* rend, Game* game, PlayState* play);
	//constructora que situa al fantasma en posicion (x,y)

	~SmartGhost();
	//destructora

	void RenderGhost(SDL_Rect rekt, PacMan* pacman);

	int getPosX();
	int getPosY();
	//metodos auxiliares
	int GetAnim();
	void Mueve(int fils, int cols);
	void CambiaDir();
	void SetInicio();

	virtual void Render();
	virtual void update();
	virtual bool loadFromFile(ifstream& archivo);
	virtual bool saveToFile(ofstream& archivo);

	void SumaEdad();
	bool esAdulto();
	bool esPadre();
	void CambiaPapa();
	bool estaMuerto();
};

