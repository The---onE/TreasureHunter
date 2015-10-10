#include "StateList.h"

bool GameOverState::checkStateChange() //状态改变返回true，状态未改变返回false，
{
	return false;
}

bool GameOverState::entryState()
{
	scene->gameOver();
	return true;
}

void GameOverState::onUpdate(float dt)
{
	time += dt;
}

bool GameOverState::exitState()
{
	return true;
}