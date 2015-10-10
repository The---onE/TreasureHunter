#pragma once

#include "Global.h"
#include "Data/SettingData.h"

class StartScene : public Scene
{
protected:
	void StartGame();
	void SetGame();
	void ResetGame();
	void PlayStopBGM();
	void OpenCloseEffect();
	void QuitGame();
	void createBackGround(string filename);

public:
	CREATE_FUNC(StartScene);
	bool init();
};

