#pragma once

#include "Global.h"
#include "Data/InteractiveData.h"

class InteractiveLayer : public Layer
{
protected:
	bool okFlag;
	bool cancelFlag;

public:
	CREATE_FUNC(InteractiveLayer);
	bool init();
	void createButton(string normal, string selected, Point pos, float size, Point anchor, void(InteractiveLayer::*func)(Ref*));

	bool checkOk();
	void responseOk();
	
	bool checkCancel();
	void responseCancel();

	void createOkButton();
	void ok(Ref* pSender);

	void createCancelButton();
	void cancel(Ref* pSender);

	//////////////////////////////////////////////////////////////////////////
	void createShowButton();
	void show(Ref* pSender);
	bool showFlag;

	void createHideButton();
	void hide(Ref* pSender);
	bool hideFlag;
	//////////////////////////////////////////////////////////////////////////
};