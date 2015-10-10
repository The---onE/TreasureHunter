#include "StateList.h"

bool InitState::checkStateChange() //状态改变返回true，状态未改变返回false，
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