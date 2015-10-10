#include "StateList.h"

bool StartState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
{
	if (time > 0)
	{
		CHANGE_TO_STATE(InitState);
	}
	return false;
}

bool StartState::entryState()
{
	scene->initBackground();
	scene->initMatrix();
	scene->initProp();
	scene->initInteractive();
	scene->initInformation();
	return true;
}

void StartState::onUpdate(float dt)
{
	time += dt;
}

bool StartState::exitState()
{
	return true;
}