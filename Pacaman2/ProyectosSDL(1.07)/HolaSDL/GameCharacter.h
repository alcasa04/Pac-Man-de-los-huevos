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

	bool loadFromFile(string filename);
	void Render();
	void update();
	bool saveToFile(string filename);
};

