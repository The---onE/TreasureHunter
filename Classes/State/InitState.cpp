#include "StateList.h"

bool InitState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
{
	if (time > 0)
	{
		CHANGE_TO_STATE(WaitActionState);
	}
	return false;
}

bool InitState::entryState()
{
	scene->initData();
	scene->initPlayers();
	scene->initLead();
	scene->randBlocks();
	return true;
}

void InitState::onUpdate(float dt)
{
	time += dt;
}

bool InitState::exitState()
{
	return true;
}