#include "StateList.h"

bool GameOverState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
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