#pragma once

#include "Global.h"
#include "Unit/PlayerUnit.h"

class Players : public Node
{
protected:
	Map<int, PlayerUnit*> allies;
	Map<int, PlayerUnit*> enemies;
	PlayerUnit* lead;
	int leadIndex;
	int aimIndex;

public:
	CREATE_FUNC(Players);
	bool init();

	PlayerUnit* createPlayer(int id, int restMoney);
	PlayerUnit* createAlly(int id, int restMoney);
	PlayerUnit* createEnemy(int id, int restMoney);

	PlayerUnit* findPlayer(int id);

	bool setLead(int id);

	int changeRestMoney(int delta);
	int changeRestMoney(int id, int delta);
	int getRestMoney();
	int getRestMoney(int id);

	int receiveOneKey();
	int receiveOneKey(int id);
	int getGainKeys();
	int getGainKeys(int id);

	int useScan();
	int useScan(int id);
	int useDig();
	int useDig(int id);
	int useDetect();
	int useDetect(int id);

	int explode();
	int explode(int id);

	int getScanPrice();
	int getScanPrice(int id);
	int getDigPrice();
	int getDigPrice(int id);
	int getDetectPrice();
	int getDetectPrice(int id);

	int getBombHurt();
	int getBombHurt(int id);
	int getTreasurePrice();
	int getTreasurePrice(int id);
};