#pragma once
#include<iostream>
#include"Game.h"

using namespace std;

class GameObject
{
	//Game* game = new Game();

public:
	GameObject();
	virtual ~GameObject()=0;
	virtual void Render()=0;
	virtual void update()=0;
	virtual bool loadFromFile(string filename) = 0;
	virtual bool saveToFile(string filename) = 0;

protected:
	Game* gueim = nullptr;

};

