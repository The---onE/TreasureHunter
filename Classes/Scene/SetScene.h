#pragma once

#include "Global.h"
#include "Data/BlockData.h"
#include "Data/PropData.h"
#include "Data/UserData.h"

class IntData
{
public:
	int data;
	string userDeafultName;
	int defaultData;
	TextField* textFiled;
	string uiName;

	IntData(const char* udn, const int dd, const string uin)
	{
		userDeafultName = string(udn);
		defaultData = dd;
		uiName = uin;
	}

	void readSet(Node* rootNode)
	{
		data = UserDefault::getInstance()->getIntegerForKey(userDeafultName.c_str(), defaultData);
		textFiled = (TextField*)(rootNode->getChildByName(uiName));
		textFiled->setString(stdItoS(data));
	}

	void getWrite(Node* rootNode)
	{
		textFiled = (TextField*)(rootNode->getChildByName(uiName));
		data = stdStoI(textFiled->getString());
		if (data < 0) return;
		UserDefault::getInstance()->setIntegerForKey(userDeafultName.c_str(), data);
	}
};

class FloatData
{
public:
	float data;
	string userDeafultName;
	float defaultData;
	TextField* textFiled;
	string uiName;

	FloatData(const char* udn, const float dd, const string uin)
	{
		userDeafultName = string(udn);
		defaultData = dd;
		uiName = uin;
	}

	void readSet(Node* rootNode)
	{
		data = UserDefault::getInstance()->getFloatForKey(userDeafultName.c_str(), defaultData);
		textFiled = (TextField*)(rootNode->getChildByName(uiName));
		textFiled->setString(stdFtoS(data));
	}

	void getWrite(Node* rootNode)
	{
		textFiled = (TextField*)(rootNode->getChildByName(uiName));
		data = stdStoF(textFiled->getString());
		if (data < 0) return;
		UserDefault::getInstance()->setFloatForKey(userDeafultName.c_str(), data);
	}
};

class SetScene : public Scene
{
protected:
	Node* rootNode;

	vector<IntData> intData;
	vector<FloatData> floatData;


public:
	CREATE_FUNC(SetScene);
	bool init();
};

