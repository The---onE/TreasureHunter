#pragma once

#include "Global.h"
#include "Data/PlayerData.h"
#include "Data/PropData.h"
#include "Data/BlockData.h"
#include "Data/UserData.h"

class PlayerUnit : public Node
{
protected:
	int id;

	int restMoney;
	int keys;

	int scanPrice;
	int digPrice;
	int detectPrice;

	int bombHurt;

public:
	CREATE_FUNC(PlayerUnit);
	bool init();
	
	void initPrice();

	void setId(int i);

	int receiveOneKey();
	int getKeys();

	void setRestMoney(int rest);
	int getRestMoney();
	int changeRestMoney(int delta);

	int useScan();
	int useDig();
	int useDetect();

	int explode();

	int getScanPrice();
	int getDigPrice();
	int getDetectPrice();

	int getBombHurt();
	int getTreasurePrice();

	//void setAttribute(int i);
	//int* getPlayerAttribute();
};