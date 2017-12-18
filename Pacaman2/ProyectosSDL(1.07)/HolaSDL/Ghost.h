#pragma once
#include"GameCharacter.h"

class Game;

class Ghost : public GameCharacter
{
private:
	
	//PacMan* pacman = nullptr;

	//Texture* textGhost = new Texture();


	//posiciones actuales e iniciales del fantasma

	int anim = 0;

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
	Ghost();
	//constructora default, situa fantasma en (0,0)

	Ghost(int x, int y, SDL_Renderer* rend, Game* game);
	//constructora que situa al fantasma en posicion (x,y)

	~Ghost();
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
};

