#pragma once
#include"GameObject.h"

using namespace std;

class GameCharacter : public GameObject
{
public:
	GameCharacter(int x, int y, Game* game);
	~GameCharacter();
protected:
	
	int IniX, IniY;

	int PosX,
		PosY;

	int dir = 0;

	Texture* text = nullptr;

	SDL_Renderer* render = nullptr;

	virtual bool loadFromFile(ifstream& archivo);
	virtual void Render();
	virtual void update();
	virtual bool saveToFile(ofstream& archivo);
};

