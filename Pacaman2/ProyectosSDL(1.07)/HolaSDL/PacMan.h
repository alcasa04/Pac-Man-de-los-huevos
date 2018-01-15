#pragma once
#include"GameCharacter.h"
#include"PacManError.h"

class Game;

enum estadoPacMan
{
	DerCerrado,
	DerAbierto,
	BotCerrado,
	BotAbierto,
	IzqCerrado,
	IzqAbierto,
	TopCerrado,
	TopAbierto,
};


class PacMan: public GameCharacter
{
private:

	//Texture* textPac = new Texture();

	//SDL_Renderer* render = nullptr;

	int auxDir=0;
	//Game * game = nullptr;
	estadoPacMan estado;
	//posicion de pacman
	int contador = 0;
	const int numTicks = 50;


	int dir2 = 0;
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
	PacMan();
	//constructora default

	PacMan(int x, int y, SDL_Renderer* render, Game* game);
	//constructora que situa pacman en una posicion

	~PacMan();
	//destructora
	bool Come = false;
	void RestartContador(int n);
	void Mueve(int fils, int cols);
	void CambiaDir(int newdir);

	void RenderPac(SDL_Rect rekt);
	int getPosX();
	int getPosY();
	estadoPacMan getEstado();
	int GetDir();
	int getTicks();
	void CambiaEstado(int i);
	void Contador();
	//metodos auxiliares

	virtual void Render();
	virtual void Update();
	virtual bool loadFromFile(ifstream& archivo);
	virtual bool saveToFile(ofstream& archivo);
};

