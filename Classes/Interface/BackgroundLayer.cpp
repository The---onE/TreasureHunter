#include "BackgroundLayer.h"

bool BackgroundLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		addSprite(bG, BACKGROUND_IMG, BACKGROUND_POSITION, BACKGROUND_SIZE, this);

		bRet = true;
	} while (0);
	return bRet;
}