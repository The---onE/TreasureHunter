#pragma once

#include "Global.h"
#include "Data/PlayerData.h"

class ResetScene : public Scene
{
protected:
	void createResetButton(string normal, string selected);
	void reset(Ref* pSender);

	void createQuitButton(string normal, string selected);
	void quitGame(Ref* pSender);

public:
	CREATE_FUNC(ResetScene);
	bool init();
};

