#include "GameCharacter.h"



GameCharacter::GameCharacter(int posx, int posy, Game* game)
{
	PosX = posx;
	PosY = posy;
	IniX = posx;
	IniY = posy;
	text = new Texture();
	dir = 0;

	gueim = game;
	/*GO->render = {
	
	};*/
	//GameObject::gueim

}
GameCharacter::~GameCharacter()
{
}

bool GameCharacter::loadFromFile(ifstream& archivo) { return true; }
void GameCharacter::Render(){}
void GameCharacter::update(){}
void GameCharacter::Mueve(int fils, int cols) {}
bool GameCharacter::saveToFile(ofstream& archivo) { return true; }
