#include "StartScene.h"
#include "GameScene.h"
#include "Scene/ResetScene.h"
#include "Scene/SetScene.h"

const Size SHADOW_OFFSIT = Size(8, -8);

bool StartScene::init()
{
	Scene::init();

	Label* startLable = Label::createWithTTF("Start Game", INFORMATION_FONT, INFORMATION_FONTSIZE);
	startLable->setTextColor(Color4B::YELLOW);
	startLable->enableShadow(Color4B::BLACK, SHADOW_OFFSIT);
	MenuItemLabel* startGame = MenuItemLabel::create(startLable, CC_CALLBACK_0(StartScene::StartGame, this));

	Label* setLable = Label::createWithTTF("Setting", INFORMATION_FONT, INFORMATION_FONTSIZE);
	setLable->setTextColor(Color4B::YELLOW);
	setLable->enableShadow(Color4B::BLACK, SHADOW_OFFSIT);
	MenuItemLabel* setGame = MenuItemLabel::create(setLable, CC_CALLBACK_0(StartScene::SetGame, this));

	Label* resetLable = Label::createWithTTF("Reset", INFORMATION_FONT, INFORMATION_FONTSIZE);
	resetLable->setTextColor(Color4B::YELLOW);
	resetLable->enableShadow(Color4B::BLACK, SHADOW_OFFSIT);
	MenuItemLabel* resetGame = MenuItemLabel::create(resetLable, CC_CALLBACK_0(StartScene::ResetGame, this));

	//////////////////////////////////////////////////////////////////////////
	bool bgmFlag = UserDefault::getInstance()->getBoolForKey(BGM_STR, BGM_DEFAULT_FLAG);

	Label* playLable = Label::createWithTTF("BGM:ON", INFORMATION_FONT, INFORMATION_FONTSIZE);
	playLable->setTextColor(Color4B::YELLOW);
	playLable->enableShadow(Color4B::BLACK, SHADOW_OFFSIT);
	MenuItemLabel* playBGM = MenuItemLabel::create(playLable);

	Label* stopLable = Label::createWithTTF("BGM:OFF", INFORMATION_FONT, INFORMATION_FONTSIZE);
	stopLable->setTextColor(Color4B::YELLOW);
	stopLable->enableShadow(Color4B::BLACK, SHADOW_OFFSIT);
	MenuItemLabel* stopBGM = MenuItemLabel::create(stopLable);

	MenuItemToggle* bgm;
	SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM, true);
	if (bgmFlag)
	{
		bgm = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::PlayStopBGM, this), playBGM, stopBGM, NULL);
	}
	else
	{
		bgm = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::PlayStopBGM, this), stopBGM, playBGM, NULL);
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	bool effectFlag = UserDefault::getInstance()->getBoolForKey(EFFECT_STR, EFFECT_DEFAULT_FLAG);

	Label* openEffectLable = Label::createWithTTF("EFFECT:ON", INFORMATION_FONT, INFORMATION_FONTSIZE);
	openEffectLable->setTextColor(Color4B::YELLOW);
	openEffectLable->enableShadow(Color4B::BLACK, SHADOW_OFFSIT);
	MenuItemLabel* openEffect = MenuItemLabel::create(openEffectLable);

	Label* closeEffectLable = Label::createWithTTF("EFFECT:OFF", INFORMATION_FONT, INFORMATION_FONTSIZE);
	closeEffectLable->setTextColor(Color4B::YELLOW);
	closeEffectLable->enableShadow(Color4B::BLACK, SHADOW_OFFSIT);
	MenuItemLabel* closeEffect = MenuItemLabel::create(closeEffectLable);

	MenuItemToggle* effect;
	if (effectFlag)
	{
		effect = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::OpenCloseEffect, this), openEffect, closeEffect, NULL);
	}
	else
	{
		effect = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::OpenCloseEffect, this), closeEffect, openEffect, NULL);
	}
	//////////////////////////////////////////////////////////////////////////

	Label* quitLable = Label::createWithTTF("Quit Game", INFORMATION_FONT, INFORMATION_FONTSIZE);
	quitLable->setTextColor(Color4B::YELLOW);
	quitLable->enableShadow(Color4B::BLACK, SHADOW_OFFSIT);
	MenuItemLabel* quitGame = MenuItemLabel::create(quitLable, CC_CALLBACK_0(StartScene::QuitGame, this));


	Menu* mainMenu = Menu::create(startGame, setGame, resetGame, bgm, effect, quitGame, NULL);
	mainMenu->alignItemsVerticallyWithPadding(20);
	this->addChild(mainMenu, 1);

	createBackGround(BACKGROUND_IMG);

	return true;
}

void StartScene::StartGame()
{
	GameScene* game = GameScene::create();
	Director::getInstance()->pushScene(game);
}

void StartScene::SetGame()
{
	SetScene* set = SetScene::create();
	Director::getInstance()->pushScene(set);
}

void StartScene::ResetGame()
{
	ResetScene* reset = ResetScene::create();
	Director::getInstance()->pushScene(reset);
}

void StartScene::PlayStopBGM()
{
	bool flag = UserDefault::getInstance()->getBoolForKey(BGM_STR, BGM_DEFAULT_FLAG);
	if (flag)
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		UserDefault::getInstance()->setBoolForKey(BGM_STR, false);
	}
	else
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		UserDefault::getInstance()->setBoolForKey(BGM_STR, true);
	}
}

void StartScene::OpenCloseEffect()
{
	bool flag = UserDefault::getInstance()->getBoolForKey(EFFECT_STR, EFFECT_DEFAULT_FLAG);
	if (flag)
	{
		UserDefault::getInstance()->setBoolForKey(EFFECT_STR, false);
	}
	else
	{
		UserDefault::getInstance()->setBoolForKey(EFFECT_STR, true);
	}
}

void StartScene::QuitGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void StartScene::createBackGround(string filename)
{
	Sprite* bG = Sprite::create(filename);
	bG->setPosition(BACKGROUND_POSITION);
	setSize(bG, BACKGROUND_SIZE);
	addChild(bG);
}
