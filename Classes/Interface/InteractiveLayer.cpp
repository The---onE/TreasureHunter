#include "InteractiveLayer.h"

bool InteractiveLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		okFlag = false;
		cancelFlag = false;
		//////////////////////////////////////////////////////////////////////////
		showFlag = false;
		createShowButton();
		hideFlag = false;
		createHideButton();
		//////////////////////////////////////////////////////////////////////////
		
		createOkButton();
		createCancelButton();

		bRet = true;
	} while (0);
	return bRet;
}

#define BUTTON_CALLBACK(__selector__,__target__, ...) std::bind(__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
void InteractiveLayer::createButton(string normal, string selected, Point pos, float size, Point anchor, void(InteractiveLayer::*func)(Ref*))
{
	auto item = MenuItemImage::create(normal, selected, BUTTON_CALLBACK(func, this));
	item->setPosition(pos);
	item->setAnchorPoint(anchor);
	setSize(item, size);
	auto menu = Menu::create(item, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}

bool InteractiveLayer::checkOk()
{
	return okFlag;
}

bool InteractiveLayer::checkCancel()
{
	return cancelFlag;
}

void InteractiveLayer::responseOk()
{
	okFlag = false;
}

void InteractiveLayer::responseCancel()
{
	cancelFlag = false;
}

void InteractiveLayer::createOkButton()
{
	createButton(OK_IMG, OK_PRESS_IMG, OK_POSITION, OK_SIZE, OK_ANCHOR, &InteractiveLayer::ok);
}
void InteractiveLayer::ok(Ref* pSender)
{
	okFlag = true;
}

void InteractiveLayer::createCancelButton()
{
	createButton(CANCEL_IMG, CANCEL_PRESS_IMG, CANCEL_POSITION, CANCEL_SIZE, CANCEL_ANCHOR, &InteractiveLayer::cancel);
}
void InteractiveLayer::cancel(Ref* pSender)
{
	cancelFlag = true;
}

//////////////////////////////////////////////////////////////////////////

void InteractiveLayer::createShowButton()
{
	createButton(SHOW_IMG, SHOW_IMG, SHOW_POSITION, SHOW_SIZE, SHOW_ANCHOR, &InteractiveLayer::show);
}
void InteractiveLayer::show(Ref* pSender)
{
	showFlag = true;
}

void InteractiveLayer::createHideButton()
{
	createButton(HIDE_IMG, HIDE_IMG, HIDE_POSITION, HIDE_SIZE, HIDE_ANCHOR, &InteractiveLayer::hide);
}
void InteractiveLayer::hide(Ref* pSender)
{
	hideFlag = true;
}

//////////////////////////////////////////////////////////////////////////