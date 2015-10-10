#pragma once

#include "Global.h"
#include "Data/PropData.h"

class PropLayer : public Layer
{
protected:
	Sprite* scanSprite;
	Sprite* digSprite;
	Sprite* detectSprite;

	Sprite* signSprite;

	bool responseFlag;
	bool signedFlag;

	int touchProp;
	int chosenProp;

public:
	CREATE_FUNC(PropLayer);
	bool init();
	void onEnter();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	void createScan();
	void createDig();
	void createDetect();

	void signProp(int prop);

	int getChosenProp();
	void deselection();
};