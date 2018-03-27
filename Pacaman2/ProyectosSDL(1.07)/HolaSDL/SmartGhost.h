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

	PacMan* pacman;
	SDL_Rect rekt;


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

	SmartGhost(int x, int y, SDL_Renderer* rend, Game* game, PlayState* play, PacMan* pac);
	//constructora que situa al fantasma en posicion (x,y)

	~SmartGhost();
	//destructora

	void RenderGhost();

	int getPosX();
	int getPosY();
	//metodos auxiliares
	int GetAnim();
	void Mueve(int fils, int cols);
	void CambiaDir();
	void SetInicio();

	virtual void Render();
	virtual void update();
	virtual bool HandleEvent(SDL_Event& evento) { return false; };
	virtual bool loadFromFile(ifstream& archivo);
	virtual bool saveToFile(ofstream& archivo);

	void SumaEdad();
	bool esAdulto();
	bool esPadre();
	void CambiaPapa();
	bool estaMuerto();
};

