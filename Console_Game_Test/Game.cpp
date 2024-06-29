#include "Game.h"
#include <stdio.h>

using namespace std;

int Game::status = -1;

Game::Game() 
{
	status = 0;
	moveCounter = 0;
}

void Game::StartGame() 
{
	setStatus(1);
}
void Game::EndGame() 
{
	setStatus(0);
}

Game::~Game() {}