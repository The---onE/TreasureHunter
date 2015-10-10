#include "ResetScene.h"

bool ResetScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Scene::init());

		createQuitButton("images/QuitNormal.png", "images/QuitSelected.png");
		createResetButton("images/reset.png", "images/reset_p.png");

		bRet = true;
	} while (0);
	return bRet;
}

void ResetScene::createResetButton(string normal, string selected)
{
	auto closeItem = MenuItemImage::create(normal, selected, CC_CALLBACK_1(ResetScene::reset, this));
	closeItem->setPosition(Point(WIDTH / 2, HEIGHT / 2));
	setSize(closeItem, 0.08f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}
void ResetScene::reset(Ref* pSender)
{
	UserDefault::getInstance()->setIntegerForKey(LEAD_REST_STR, BEGINNING_MONEY);
}

void ResetScene::createQuitButton(string normal, string selected)
{
	auto closeItem = MenuItemImage::create(normal, selected, CC_CALLBACK_1(ResetScene::quitGame, this));
	closeItem->setPosition(Point(WIDTH / 2, 0));
	closeItem->setAnchorPoint(Point(0.5f, 0));
	setSize(closeItem, 0.08f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}
void ResetScene::quitGame(Ref* pSender)
{
	Director::getInstance()->popScene();
}
