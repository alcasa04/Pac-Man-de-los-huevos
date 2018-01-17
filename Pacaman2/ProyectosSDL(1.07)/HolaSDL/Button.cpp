#include "Button.h"
#include"GameObject.h"


Button::Button(SDL_Rect rect, Texture* textura, Game* game, CallBackOnClick* cbonclk, string filename) //: GameObject()
{
	destRect = rect;
	text = textura;
	gueim = game;
	cbOnClick = cbonclk;

	text->loadText(filename, 1, 1, gueim->getRender());
}

Button::~Button()
{
}

bool Button::HandleEvent(SDL_Event& e) {
	bool handled = false;
	//CallBackOnClick cbOnClk;
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		SDL_Point p;
		SDL_GetMouseState(&p.x, &p.y);
		if (SDL_PointInRect(&p, &destRect)) {
			handled = true;
			cbOnClick(gueim);
		}
		return handled;
	}
}

void Button::Render() {
	text->Render(destRect, gueim->getRender());
}

void Button::update(){}
/*
bool Button::loadFromFile(string filename) { return true; }
bool Button::saveToFile(string filename) { return true; }*/
