#pragma once
#include"GameCharacter.h"

class Game;

class SmartGhost : public GameCharacter
{
private:

	//PacMan* pacman = nullptr;

	//Texture* textGhost = new Texture();


	//posiciones actuales e iniciales del fantasma

	int anim = 0;
	float edad = 5;

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

	SmartGhost(int x, int y, SDL_Renderer* rend, Game* game);
	//constructora que situa al fantasma en posicion (x,y)

	~SmartGhost();
	//destructora

	void RenderGhost(SDL_Rect rekt, int d, PacMan* pacman);

	int getPosX();
	int getPosY();
	//metodos auxiliares
	int GetAnim();
	void Mueve(int fils, int cols);
	void CambiaDir();
	void SetInicio();

	void Render();
	void update();
	bool loadFromFile(string filename);
	bool saveToFile(string filename);

	void SumaEdad();
};

