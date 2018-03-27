#pragma once
#include"PacManObject.h"

using namespace std;

class GameCharacter : public PacManObject
{
public:
	GameCharacter(int x, int y, Game* game);
	~GameCharacter();
	virtual void Render();
	virtual void Mueve(int fils, int cols);
	virtual void update();
protected:
	
	int IniX, IniY;

	int PosX,
		PosY;

	int dir = 0;

	Texture* text = nullptr;

	SDL_Renderer* render = nullptr;

	virtual bool loadFromFile(ifstream& archivo);

	virtual bool saveToFile(ofstream& archivo);
};

