#include "GameStateMachine.h"

GameStateMachine::GameStateMachine()
{

}

GameStateMachine::~GameStateMachine()
{

}

GameState* GameStateMachine::CurrentState() { return gameStack.top(); }

void GameStateMachine::PushState(GameState* next) 
{
	gameStack.push(next); }

void GameStateMachine::PopState() {
	GameState* aux = gameStack.top();
	gameStack.pop();
	delete aux;
}

/*
calss playstate: gamestate{
uint
.
.
.
gamemap* map;
pacman* pac;
.
.
void handleeventi(sdl_event& e){
if(e.type == sdl_keydown){
if(e.key... == sdlk_escpae)
app->getStateMachine()->pushState(new PauseState(app);
else pacman-> andleevent(e);
}
}

void update(){
gamestate::update();
if(...)
//paso de nivel
load level();

class pausestate:public gamestate{
pusetate(sdlapp* app):gamestate(app)

stage->pushback(new button(app,app->getTexture(ResumeButtonTexture//es un numero identificador de la textura, buttonW, buttonH, x, y, ...)));
stage->pushback(new button(...);

class button : public gameobject{
uint x,y,w,h;
texture* text;
|
\/
bool handleEvent(...e){
if(pulsado de boton....)´{
	if(sdl-pointInRect(...)//dice si el click esta dentro de un rectangulo
		cout<<"boton pulsado";*/
