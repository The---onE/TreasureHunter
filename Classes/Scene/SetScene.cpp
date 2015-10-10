#include "SetScene.h"

bool SetScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Scene::init());

		rootNode = CSLoader::createNode("SetScene.csb");
		addChild(rootNode);

		intData.push_back(IntData(KEY_NUM_STR, KEY_NUM, KEY_NUM_UI));
		intData.push_back(IntData(GOLD_NUM_STR, GOLD_NUM, GOLD_NUM_UI));
		intData.push_back(IntData(BOMB_NUM_STR, BOMB_NUM, BOMB_NUM_UI));
		intData.push_back(IntData(SCAN_BASE_PRICE_STR, SCAN_BASE_PRICE, SCAN_BASE_PRICE_UI));
		intData.push_back(IntData(DIG_BASE_PRICE_STR, DIG_BASE_PRICE, DIG_BASE_PRICE_UI));
		intData.push_back(IntData(DETECT_BASE_PRICE_STR, DETECT_BASE_PRICE, DETECT_BASE_PRICE_UI));
		intData.push_back(IntData(GOLD_PRICE_STR, GOLD_PRICE, GOLD_PRICE_UI));
		intData.push_back(IntData(BOMB_BASE_HURT_STR, BOMB_BASE_HURT, BOMB_BASE_HURT_UI));
		intData.push_back(IntData(TREASURE_BASE_PRICE_STR, TREASURE_BASE_PRICE, TREASURE_BASE_PRICE_UI));

		floatData.push_back(FloatData(SCAN_INCREASE_COEFFICIENT_STR, SCAN_INCREASE_COEFFICIENT, SCAN_INCREASE_COEFFICIENT_UI));
		floatData.push_back(FloatData(DIG_INCREASE_COEFFICIENT_STR, DIG_INCREASE_COEFFICIENT, DIG_INCREASE_COEFFICIENT_UI));
		floatData.push_back(FloatData(DETECT_INCREASE_COEFFICIENT_STR, DETECT_INCREASE_COEFFICIENT, DETECT_INCREASE_COEFFICIENT_UI));
		floatData.push_back(FloatData(HURT_INCREASE_COEFFICIENT_STR, HURT_INCREASE_COEFFICIENT, HURT_INCREASE_COEFFICIENT_UI));
		floatData.push_back(FloatData(TREASURE_INCREASE_COEFFICIENT_STR, TREASURE_INCREASE_COEFFICIENT, TREASURE_INCREASE_COEFFICIENT_UI));

		for (vector<IntData>::iterator it = intData.begin(); it != intData.end(); ++it)
		{
			it->readSet(rootNode);
		}
		for (vector<FloatData>::iterator it = floatData.begin(); it != floatData.end(); ++it)
		{
			it->readSet(rootNode);
		}


		Button* ok = (Button*)(rootNode->getChildByName("OK"));
		ok->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				for (vector<IntData>::iterator it = intData.begin(); it != intData.end(); ++it)
				{
					it->getWrite(rootNode);
				}
				for (vector<FloatData>::iterator it = floatData.begin(); it != floatData.end(); ++it)
				{
					it->getWrite(rootNode);
				}

				UserDefault::getInstance()->flush();

				Director::getInstance()->popScene();
			}
		});

		Button* cancel = (Button*)(rootNode->getChildByName("Cancel"));
		cancel->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Director::getInstance()->popScene();
			}
		});

		bRet = true;
	} while (0);
	return bRet;
}