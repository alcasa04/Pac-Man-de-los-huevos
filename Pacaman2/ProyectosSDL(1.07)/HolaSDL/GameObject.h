#pragma once
#include<iostream>
#include "Game.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject()=0;
	virtual void Render()=0;
	virtual void update()=0;
	virtual bool loadFromFile(ifstream& archivo) = 0;
	virtual bool saveToFile(ofstream& archivo) = 0;

protected:
	Game* gueim = nullptr;

};

