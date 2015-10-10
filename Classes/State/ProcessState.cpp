#include "StateList.h"

bool ProcessState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
{
	if (time > PROCESS_TIME)
		CHANGE_TO_STATE(WaitActionState);

	return false;
}

bool ProcessState::entryState()
{
	return true;
}

void ProcessState::onUpdate(float dt)
{
	time += dt;
}

bool ProcessState::exitState()
{
	return true;
}