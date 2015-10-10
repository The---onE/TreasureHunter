#include "StateList.h"

bool WaitActionState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
{
	int event = scene->checkOk();
	switch (event)
	{
	case GET_TREASURE:
		CHANGE_TO_STATE(GameOverState)
		break;
	case COMMONLY_EVENT:
		CHANGE_TO_STATE(ProcessState);
		break;
	case NO_EVENT:
		break;
	default:
		break;
	}

	return false;
}

bool WaitActionState::entryState()
{
	return true;
}

void WaitActionState::onUpdate(float dt)
{
	time += dt;
	scene->checkCancel();

	//////////////////////////////////////////////////////////////////////////
	scene->checkShow();
	scene->checkHide();
	//////////////////////////////////////////////////////////////////////////
}

bool WaitActionState::exitState()
{
	return true;
}