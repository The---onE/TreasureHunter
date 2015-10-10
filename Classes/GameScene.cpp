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

		createQuitButton("images/QuitNormal.png", "images/QuitSelected.png"); //����˳���Ϸ��ť
		stateMachine = StateMachine::createWithGameScene(this); //����״̬��
		stateMachine->changeState(StartState::create(this)); //����׼����ʼ��Ϸ״̬
		this->scheduleUpdate();

		bRet = true;
	} while (0);
	return bRet;
}

//��ʼ���û�����
void GameScene::initData()
{
	//��UserDefault�ж�ȡ�Զ������ݣ���δ�����������ΪĬ��ֵ
	//�Զ������ݴ����Data/UserData.cpp�ж����ȫ�ֱ�����
	auto f = UserDefault::getInstance();
	KeyNum = f->getIntegerForKey(KEY_NUM_STR, KEY_NUM); //Կ������
	GoldNum = f->getIntegerForKey(GOLD_NUM_STR, GOLD_NUM); //�������
	BombNum = f->getIntegerForKey(BOMB_NUM_STR, BOMB_NUM); //ը������

	ScanBasePrice = f->getIntegerForKey(SCAN_BASE_PRICE_STR, SCAN_BASE_PRICE); //ɨ������۸�
	ScanIncreaseCoefficient = f->getFloatForKey(SCAN_INCREASE_COEFFICIENT_STR, SCAN_INCREASE_COEFFICIENT); //ɨ��۸�����ϵ��
	DigBasePrice = f->getIntegerForKey(DIG_BASE_PRICE_STR, DIG_BASE_PRICE); //�ھ�����۸�
	DigIncreaseCoefficient = f->getFloatForKey(DIG_INCREASE_COEFFICIENT_STR, DIG_INCREASE_COEFFICIENT); //�ھ�۸�����ϵ��
	DetectBasePrice = f->getIntegerForKey(DETECT_BASE_PRICE_STR, DETECT_BASE_PRICE); //̽������۸�
	DetectIncreaseCoefficient = f->getFloatForKey(DETECT_INCREASE_COEFFICIENT_STR, DETECT_INCREASE_COEFFICIENT); //̽��۸�����ϵ��

	GoldPrice = f->getIntegerForKey(GOLD_PRICE_STR, GOLD_PRICE); //�ڳ���������Ǯ
	BombBaseHurt = f->getIntegerForKey(BOMB_BASE_HURT_STR, BOMB_BASE_HURT); //�ڳ�ը����ʧ��Ǯ
	HurtIncreaseCoefficient = f->getFloatForKey(HURT_INCREASE_COEFFICIENT_STR, HURT_INCREASE_COEFFICIENT); //�ڳ�ը����ʧ��Ǯ����ϵ��
	TreasureBasePrice = f->getIntegerForKey(TREASURE_BASE_PRICE_STR, TREASURE_BASE_PRICE); //�ڳ��������û�����Ǯ
	TreasureIncreaseCoefficient = f->getFloatForKey(TREASURE_INCREASE_COEFFICIENT_STR, TREASURE_INCREASE_COEFFICIENT); //���ؼ۸�����ϵ��
}

//��ʼ��������
void GameScene::initBackground()
{
	background = BackgroundLayer::create();
	addChild(background);
}

//��ʼ�������
void GameScene::initMatrix()
{
	matrix = MatrixLayer::create();
	addChild(matrix);
}

//��ʼ����Ϣ��
void GameScene::initInformation()
{
	information = InformationLayer::create();
	addChild(information);
}

//��ʼ�����߲�
void GameScene::initProp()
{
	prop = PropLayer::create();
	addChild(prop);
}

//��ʼ��������
void GameScene::initInteractive()
{
	interactive = InteractiveLayer::create();
	addChild(interactive);
}

//��ʼ�������Ϣ
void GameScene::initPlayers()
{
	players = Players::create();
	addChild(players);
}

//��ʼ���ٿ���
void GameScene::initLead()
{
	int restMoney = UserDefault::getInstance()->getIntegerForKey(LEAD_REST_STR, BEGINNING_MONEY); //��ȡ�ٿ���ʣ���Ǯ
	players->createAlly(LEAD_ID, restMoney);
	players->setLead(LEAD_ID);

	gameMoney = 0; //��ʼ�����ֱ�������
	showInformation(); //��ʾ�ٿ�����Ϣ
	showPrice();
}

//����ھ�����������Ʒ
void GameScene::randBlocks()
{
	matrix->randBlock();
	showRest(); //��ʼ����Ʒʣ������
}

//����û�ѡ��ĵ��ߺ͸���
void GameScene::clearSelect()
{
	matrix->signClear();
	prop->deselection();
}

//��鲢��Ӧ����ȷ����ť
int GameScene::checkOk()
{
	int event = NO_EVENT;
	if (interactive->checkOk())
	{
		//������ȷ����ť
		int ch = prop->getChosenProp(); //�û�ѡ��ĵ���
		Coord c = matrix->getSignedCoord(); //�û�ѡ��ĸ���
		switch (ch)
		{
		case SCAN: //��ѡ����ɨ��
			if (c.line != NO_SIGN && c.row != NO_SIGN) //��ѡ���˸���
			{
				event = COMMONLY_EVENT; //Ϊ�����¼�
				int scanPrice = players->useScan(); //��ȡɨ��۸�
				if (scanPrice >= 0)
				{
					gameMoney -= scanPrice; //����Ǯ�㹻��ʹ��
				}
				else
				{
					moneyNotEnough(); //����Ǯ���㣬����ʾ�Ҳ�����
					break;
				}
				matrix->scan(); //ɨ����Χ����
				clearSelect();
				showInformation();
				showPrice();
			}
			break;
		case DETECT: //��ѡ��̽��
			if (c.line != NO_SIGN && c.row != NO_SIGN) //��ѡ���˸���
			{
				event = COMMONLY_EVENT; // Ϊ�����¼�
				int detectPrice = players->useDetect(); //��ȡ̽��۸�
				if (detectPrice >= 0)
				{
					gameMoney -= detectPrice; //����Ǯ�㹻��ʹ��
				}
				else
				{
					moneyNotEnough(); //����Ǯ���㣬����ʾ�Ҳ�����
					break;
				}
				matrix->detect(); //̽����Χ����
				clearSelect();
				showInformation();
				showPrice();
			}
			break;
		case DIG: //��ѡ���ھ�
			if (c.line != NO_SIGN && c.row != NO_SIGN) //��ѡ���˸���
			{
				int it = matrix->getSignedItem(); //��ȡѡ������е���Ʒ
				if (it != PIT) //��ѡ��ĸ����ѱ��ھ���Ϊ��Ч����
				{
					event = COMMONLY_EVENT; //Ϊ�����¼�
					int digPrice = players->useDig(); //��ȡ�ھ�۸�
					if (digPrice >= 0)
					{
						gameMoney -= digPrice; //����Ǯ�㹻��ʹ��
					}
					else
					{
						moneyNotEnough(); //����Ǯ���㣬����ʾ�Ҳ�����
						break;
					}
					matrix->dig(); //��ʾ�ھ��Ӧ��Ʒ����Ч
					clearSelect();
					switch (it)
					{
					case KEY: //���ڳ���Կ��
						players->receiveOneKey();
						break;
					case GOLD: //���ڳ��˽��
						//��ý�Ǯ
						gameMoney += GoldPrice;
						players->changeRestMoney(GoldPrice);
						break;
					case TREASURE: //���ڳ��˱���
						//��ý�Ǯ
						gameMoney += players->getTreasurePrice();
						players->changeRestMoney(players->getTreasurePrice());
						event = GET_TREASURE; //�ڳ�������һ����Ϸ�����ı�־
						break;
					case BOMB: //���ڳ�ը��
						gameMoney -= players->explode(); //��ʧ��Ǯ
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

//��鲢��Ӧ����ȡ����ť
void GameScene::checkCancel()
{
	if (interactive->checkCancel())
	{
		//������ȡ����ť������û�ѡ��ĵ��ߺ͸���
		clearSelect();

		interactive->responseCancel();
	}
}

//��ʾ��Ϸ��Ϣ
void GameScene::showInformation()
{
	information->changeRestMoneyLabel(players->getRestMoney()); //��ʾʣ���Ǯ
	information->changeGameMoneyLabel(gameMoney); //��ʾ������Ϸ����
	information->changeGainKeysLabel(players->getGainKeys()); //��ʾ�ѻ��Կ����
	information->changeGoldPriceLabel(GoldPrice); //��ʾ�ڳ���ҿɻ�õĽ�Ǯ
	information->changeBombHurtLabel(players->getBombHurt()); //��ʾ�ڳ�ը����ʧ�Ľ�Ǯ
	information->changeTreasurePriceLabel(players->getTreasurePrice()); //��ʾ�ڳ����ؿɻ�õĽ�Ǯ

	UserDefault::getInstance()->setIntegerForKey(LEAD_REST_STR, players->getRestMoney()); //��ʣ��Ľ�Ǯд��UserDefault�ļ���
	UserDefault::getInstance()->flush();
}

//��ʾʹ�õ��߼۸�
void GameScene::showPrice()
{
	information->changeScanPriceLabel(players->getScanPrice()); //��ʾʹ��ɨ��۸�
	information->changeDigPriceLabel(players->getDigPrice()); //��ʾʹ���ھ�۸�
	information->changeDetectPriceLabel(players->getDetectPrice()); //��ʾʹ��̽��۸�
}

//��ʾ��������Ʒʣ������
void GameScene::showRest()
{
	information->changeRestKeyLabel(matrix->getRestKey()); //���ʣ��Կ����
	information->changeRestGoldLabel(matrix->getRestGold()); //��ʾʣ������
	information->changeRestBombLabel(matrix->getRestBomb()); //��ʾʣ��ը����
}

//��Ǯ������߼۸�ʱ����ʾ
void GameScene::moneyNotEnough()
{
	char text[32];
	sprintf(text, "You Money Is Not Enough!");
	Label* l = Label::createWithTTF(text, INFORMATION_FONT, INFORMATION_FONTSIZE); //����Label
	l->setTextColor(Color4B::RED); //������ɫ
	l->enableShadow(Color4B::BLACK, Size(3, -3)); //�����Ӱ 
	l->setPosition(WIDTH / 2, HEIGHT / 2);
	setSize(l, 0.035f); //���ô�С
	this->addChild(l);

	Action* a = Sequence::create(FadeOut::create(2.5f), RemoveSelf::create(), NULL); //����Ч����������ɾ������
	l->runAction(a);
}

//��Ϸ����ʱ����ʾ
void GameScene::gameOver()
{
	char text[128];
	Color4B c;
	if (gameMoney > 0) //���þ���Ϸ׬��Ǯ
	{
		sprintf(text, "You Get $%d In This Game!\nPress To Start A New Game.", gameMoney);
		c = Color4B::GREEN;
		//��������Ч���򲥷�ʤ����Ч
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_STR, EFFECT_DEFAULT_FLAG))
			SimpleAudioEngine::getInstance()->playEffect(WIN_EFFECT);
	}
	else //���þ���Ϸ��ʧǮ
	{
		sprintf(text, "You Lose $%d In This Game...\nPress To Start A New Game.", -gameMoney);
		c = Color4B::RED;
		//��������Ч���򲥷�ʧ����Ч
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_STR, EFFECT_DEFAULT_FLAG))
			SimpleAudioEngine::getInstance()->playEffect(LOSE_EFFECT);
	}
	Label* label = Label::createWithTTF(text, INFORMATION_FONT, 40); //����Label
	label->setTextColor(c);
	label->enableShadow(Color4B::BLACK, Size(5, -5)); //�����Ӱ

	MenuItemLabel* re = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::restart, this)); //�����˵������ʱ���ÿ�ʼ����Ϸ����
	Menu* menu = Menu::create(re, NULL);
	addChild(menu, 1000);
}

//��ʼ����Ϸ
void GameScene::restart(Ref* pSender)
{
	Scene* s = GameScene::create();
	Director::getInstance()->replaceScene(s); //���µ�Game�����滻ԭ��������ʼ����Ϸ
}

//�����˳���Ϸ��ť
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
//�˳���Ϸ
void GameScene::quitGame(Ref* pSender)
{
	Director::getInstance()->popScene(); //������һ����
}


//����ʱʹ�õĺ���
//////////////////////////////////////////////////////////////////////////
//��鲢��Ӧ����ȫ����ʾ��ť
void GameScene::checkShow()
{
	if (interactive->showFlag) //������ȫ����ʾ��ť
	{
		matrix->showAllItem(SHOW_ITEM_TIME); //��ʾ������ȫ����Ʒ

		interactive->showFlag = false;
	}
}

//��鲢��Ӧ����ȫ�����ذ�ť
void GameScene::checkHide()
{
	if (interactive->hideFlag) //������ȫ�����ذ�ť
	{
		matrix->hideAllItem(SHOW_ITEM_TIME); //���ؾ�����ȫ����Ʒ
		interactive->hideFlag = false;
	}
}
//////////////////////////////////////////////////////////////////////////

//����״̬��ָ��
StateMachine* GameScene::getStateMachine()
{
	return stateMachine;
}
//��Ϸ��ѭ��
void GameScene::update(float dt)
{
	stateMachine->update(dt); //��Ϸ��ѭ����״̬������
}