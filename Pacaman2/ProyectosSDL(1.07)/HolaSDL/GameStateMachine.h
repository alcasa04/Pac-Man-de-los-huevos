#pragma once
#include<iostream>
#include<stack>

using namespace std;

class GameState;
class Game;
class GameMap;
class PacMan;
class Ghost;
class SmartGhost;

class GameStateMachine
{
private:
	stack<GameState*> gameStack;
public:
	GameStateMachine();
	~GameStateMachine();
	//void PushState(GameState newstate);
};

