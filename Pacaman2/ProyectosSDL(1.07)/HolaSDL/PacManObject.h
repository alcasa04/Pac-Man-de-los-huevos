#pragma once
#include"GameObject.h"

class PlayState;

class PacManObject: public GameObject
{
protected:
	PlayState* play = nullptr;
public:
	virtual bool loadFromFile(ifstream& archivo) = 0;
	virtual bool saveToFile(ofstream& archivo) = 0;
	PacManObject();
	~PacManObject();
};

