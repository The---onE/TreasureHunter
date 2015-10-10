#include "GameScene.h"
#include "State/StateList.h"

bool GameScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Scene::init());

		//auto rootNode = CSLoader::createNode("MainScene.csb");
		//addChild(rootNode);

		createQuitButton("images/QuitNormal.png", "images/QuitSelected.png"); //添加退出游戏按钮
		stateMachine = StateMachine::createWithGameScene(this); //创建状态机
		stateMachine->changeState(StartState::create(this)); //进入准备开始游戏状态
		this->scheduleUpdate();

		bRet = true;
	} while (0);
	return bRet;
}

//初始化用户数据
void GameScene::initData()
{
	//从UserDefault中读取自定义数据，若未定义过则设置为默认值
	//自定义数据存放于Data/UserData.cpp中定义的全局变量中
	auto f = UserDefault::getInstance();
	KeyNum = f->getIntegerForKey(KEY_NUM_STR, KEY_NUM); //钥匙数量
	GoldNum = f->getIntegerForKey(GOLD_NUM_STR, GOLD_NUM); //金币数量
	BombNum = f->getIntegerForKey(BOMB_NUM_STR, BOMB_NUM); //炸弹数量

	ScanBasePrice = f->getIntegerForKey(SCAN_BASE_PRICE_STR, SCAN_BASE_PRICE); //扫描基础价格
	ScanIncreaseCoefficient = f->getFloatForKey(SCAN_INCREASE_COEFFICIENT_STR, SCAN_INCREASE_COEFFICIENT); //扫描价格增长系数
	DigBasePrice = f->getIntegerForKey(DIG_BASE_PRICE_STR, DIG_BASE_PRICE); //挖掘基础价格
	DigIncreaseCoefficient = f->getFloatForKey(DIG_INCREASE_COEFFICIENT_STR, DIG_INCREASE_COEFFICIENT); //挖掘价格增长系数
	DetectBasePrice = f->getIntegerForKey(DETECT_BASE_PRICE_STR, DETECT_BASE_PRICE); //探测基础价格
	DetectIncreaseCoefficient = f->getFloatForKey(DETECT_INCREASE_COEFFICIENT_STR, DETECT_INCREASE_COEFFICIENT); //探测价格增长系数

	GoldPrice = f->getIntegerForKey(GOLD_PRICE_STR, GOLD_PRICE); //挖出金币所获金钱
	BombBaseHurt = f->getIntegerForKey(BOMB_BASE_HURT_STR, BOMB_BASE_HURT); //挖出炸弹损失金钱
	HurtIncreaseCoefficient = f->getFloatForKey(HURT_INCREASE_COEFFICIENT_STR, HURT_INCREASE_COEFFICIENT); //挖出炸弹损失金钱增长系数
	TreasureBasePrice = f->getIntegerForKey(TREASURE_BASE_PRICE_STR, TREASURE_BASE_PRICE); //挖出宝藏所得基础金钱
	TreasureIncreaseCoefficient = f->getFloatForKey(TREASURE_INCREASE_COEFFICIENT_STR, TREASURE_INCREASE_COEFFICIENT); //宝藏价格增长系数
}

//初始化背景层
void GameScene::initBackground()
{
	background = BackgroundLayer::create();
	addChild(background);
}

//初始化矩阵层
void GameScene::initMatrix()
{
	matrix = MatrixLayer::create();
	addChild(matrix);
}

//初始化信息层
void GameScene::initInformation()
{
	information = InformationLayer::create();
	addChild(information);
}

//初始化道具层
void GameScene::initProp()
{
	prop = PropLayer::create();
	addChild(prop);
}

//初始化交互层
void GameScene::initInteractive()
{
	interactive = InteractiveLayer::create();
	addChild(interactive);
}

//初始化玩家信息
void GameScene::initPlayers()
{
	players = Players::create();
	addChild(players);
}

//初始化操控者
void GameScene::initLead()
{
	int restMoney = UserDefault::getInstance()->getIntegerForKey(LEAD_REST_STR, BEGINNING_MONEY); //获取操控者剩余金钱
	players->createAlly(LEAD_ID, restMoney);
	players->setLead(LEAD_ID);

	gameMoney = 0; //初始化本局比赛收益
	showInformation(); //显示操控者信息
	showPrice();
}

//随机在矩阵中生成物品
void GameScene::randBlocks()
{
	matrix->randBlock();
	showRest(); //初始化物品剩余数量
}

//清除用户选择的道具和格子
void GameScene::clearSelect()
{
	matrix->signClear();
	prop->deselection();
}

//检查并响应按下确定按钮
int GameScene::checkOk()
{
	int event = NO_EVENT;
	if (interactive->checkOk())
	{
		//若按下确定按钮
		int ch = prop->getChosenProp(); //用户选择的道具
		Coord c = matrix->getSignedCoord(); //用户选择的格子
		switch (ch)
		{
		case SCAN: //若选择了扫描
			if (c.line != NO_SIGN && c.row != NO_SIGN) //若选择了格子
			{
				event = COMMONLY_EVENT; //为基本事件
				int scanPrice = players->useScan(); //获取扫描价格
				if (scanPrice >= 0)
				{
					gameMoney -= scanPrice; //若金钱足够则使用
				}
				else
				{
					moneyNotEnough(); //若金钱不足，则提示且不操作
					break;
				}
				matrix->scan(); //扫描周围格子
				clearSelect();
				showInformation();
				showPrice();
			}
			break;
		case DETECT: //若选择探测
			if (c.line != NO_SIGN && c.row != NO_SIGN) //若选择了格子
			{
				event = COMMONLY_EVENT; // 为基本事件
				int detectPrice = players->useDetect(); //获取探测价格
				if (detectPrice >= 0)
				{
					gameMoney -= detectPrice; //若金钱足够则使用
				}
				else
				{
					moneyNotEnough(); //若金钱不足，则提示且不操作
					break;
				}
				matrix->detect(); //探测周围格子
				clearSelect();
				showInformation();
				showPrice();
			}
			break;
		case DIG: //若选择挖掘
			if (c.line != NO_SIGN && c.row != NO_SIGN) //若选择了格子
			{
				int it = matrix->getSignedItem(); //获取选择格子中的物品
				if (it != PIT) //若选择的格子已被挖掘，则为无效操作
				{
					event = COMMONLY_EVENT; //为基本事件
					int digPrice = players->useDig(); //获取挖掘价格
					if (digPrice >= 0)
					{
						gameMoney -= digPrice; //若金钱足够则使用
					}
					else
					{
						moneyNotEnough(); //若金钱不足，则提示且不操作
						break;
					}
					matrix->dig(); //显示挖掘对应物品的特效
					clearSelect();
					switch (it)
					{
					case KEY: //若挖出了钥匙
						players->receiveOneKey();
						break;
					case GOLD: //若挖出了金币
						//获得金钱
						gameMoney += GoldPrice;
						players->changeRestMoney(GoldPrice);
						break;
					case TREASURE: //若挖出了宝藏
						//获得金钱
						gameMoney += players->getTreasurePrice();
						players->changeRestMoney(players->getTreasurePrice());
						event = GET_TREASURE; //挖出宝藏是一局游戏结束的标志
						break;
					case BOMB: //若挖出炸弹
						gameMoney -= players->explode(); //损失金钱
						break;
					case NO_ITEM:
						break;
					default:
						break;
					}
					showInformation();
					showPrice();
					showRest();
				}
			}
			break;
		case NO_PROP:
		default:
			break;
		}

		interactive->responseOk();
	}
	return event;
}

//检查并响应按下取消按钮
void GameScene::checkCancel()
{
	if (interactive->checkCancel())
	{
		//若按下取消按钮，清除用户选择的道具和格子
		clearSelect();

		interactive->responseCancel();
	}
}

//显示游戏信息
void GameScene::showInformation()
{
	information->changeRestMoneyLabel(players->getRestMoney()); //显示剩余金钱
	information->changeGameMoneyLabel(gameMoney); //显示本局游戏收益
	information->changeGainKeysLabel(players->getGainKeys()); //显示已获得钥匙数
	information->changeGoldPriceLabel(GoldPrice); //显示挖出金币可获得的金钱
	information->changeBombHurtLabel(players->getBombHurt()); //显示挖出炸弹损失的金钱
	information->changeTreasurePriceLabel(players->getTreasurePrice()); //显示挖出宝藏可获得的金钱

	UserDefault::getInstance()->setIntegerForKey(LEAD_REST_STR, players->getRestMoney()); //将剩余的金钱写入UserDefault文件中
	UserDefault::getInstance()->flush();
}

//显示使用道具价格
void GameScene::showPrice()
{
	information->changeScanPriceLabel(players->getScanPrice()); //显示使用扫描价格
	information->changeDigPriceLabel(players->getDigPrice()); //显示使用挖掘价格
	information->changeDetectPriceLabel(players->getDetectPrice()); //显示使用探测价格
}

//显示矩阵中物品剩余数量
void GameScene::showRest()
{
	information->changeRestKeyLabel(matrix->getRestKey()); //娴熟剩余钥匙数
	information->changeRestGoldLabel(matrix->getRestGold()); //显示剩余金币数
	information->changeRestBombLabel(matrix->getRestBomb()); //显示剩余炸弹数
}

//金钱不足道具价格时的提示
void GameScene::moneyNotEnough()
{
	char text[32];
	sprintf(text, "You Money Is Not Enough!");
	Label* l = Label::createWithTTF(text, INFORMATION_FONT, INFORMATION_FONTSIZE); //创建Label
	l->setTextColor(Color4B::RED); //设置颜色
	l->enableShadow(Color4B::BLACK, Size(3, -3)); //添加阴影 
	l->setPosition(WIDTH / 2, HEIGHT / 2);
	setSize(l, 0.035f); //设置大小
	this->addChild(l);

	Action* a = Sequence::create(FadeOut::create(2.5f), RemoveSelf::create(), NULL); //淡出效果，结束后删除自身
	l->runAction(a);
}

//游戏结束时的提示
void GameScene::gameOver()
{
	char text[128];
	Color4B c;
	if (gameMoney > 0) //若该局游戏赚到钱
	{
		sprintf(text, "You Get $%d In This Game!\nPress To Start A New Game.", gameMoney);
		c = Color4B::GREEN;
		//若开启音效，则播放胜利音效
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_STR, EFFECT_DEFAULT_FLAG))
			SimpleAudioEngine::getInstance()->playEffect(WIN_EFFECT);
	}
	else //若该局游戏损失钱
	{
		sprintf(text, "You Lose $%d In This Game...\nPress To Start A New Game.", -gameMoney);
		c = Color4B::RED;
		//若开启音效，则播放失败音效
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_STR, EFFECT_DEFAULT_FLAG))
			SimpleAudioEngine::getInstance()->playEffect(LOSE_EFFECT);
	}
	Label* label = Label::createWithTTF(text, INFORMATION_FONT, 40); //创建Label
	label->setTextColor(c);
	label->enableShadow(Color4B::BLACK, Size(5, -5)); //添加阴影

	MenuItemLabel* re = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::restart, this)); //创建菜单项，按下时调用开始新游戏函数
	Menu* menu = Menu::create(re, NULL);
	addChild(menu, 1000);
}

//开始新游戏
void GameScene::restart(Ref* pSender)
{
	Scene* s = GameScene::create();
	Director::getInstance()->replaceScene(s); //用新的Game场景替换原场景，开始新游戏
}

//创建退出游戏按钮
void GameScene::createQuitButton(string normal, string selected)
{
	auto closeItem = MenuItemImage::create(normal, selected, CC_CALLBACK_1(GameScene::quitGame, this));
	closeItem->setPosition(Point(WIDTH / 2, 0));
	closeItem->setAnchorPoint(Point(0.5f, 0));
	setSize(closeItem, 0.08f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}
//退出游戏
void GameScene::quitGame(Ref* pSender)
{
	Director::getInstance()->popScene(); //返回上一场景
}


//测试时使用的后门
//////////////////////////////////////////////////////////////////////////
//检查并响应按下全部显示按钮
void GameScene::checkShow()
{
	if (interactive->showFlag) //若按下全部显示按钮
	{
		matrix->showAllItem(SHOW_ITEM_TIME); //显示矩阵中全部物品

		interactive->showFlag = false;
	}
}

//检查并响应按下全部隐藏按钮
void GameScene::checkHide()
{
	if (interactive->hideFlag) //若按下全部隐藏按钮
	{
		matrix->hideAllItem(SHOW_ITEM_TIME); //隐藏矩阵中全部物品
		interactive->hideFlag = false;
	}
}
//////////////////////////////////////////////////////////////////////////

//返回状态机指针
StateMachine* GameScene::getStateMachine()
{
	return stateMachine;
}
//游戏主循环
void GameScene::update(float dt)
{
	stateMachine->update(dt); //游戏主循环由状态机调度
}