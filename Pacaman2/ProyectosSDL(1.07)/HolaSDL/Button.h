#pragma once
#include"GameObject.h"

class Button:public GameObject
{
private:
	typedef void CallBackOnClick(Game* game);
	SDL_Rect destRect;
	Texture* text;
protected:
	CallBackOnClick* cbOnClick;
public:
	Button(SDL_Rect rect, Texture* text, Game* game, CallBackOnClick* cboclk, string filename);
	~Button();
	bool HandleEvent(SDL_Event& e);
		void update();
	void Render();
		//bool loadFromFile(string filename);
		//bool saveToFile(string filename);
};

