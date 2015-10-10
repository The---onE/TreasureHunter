#include "Players.h"

bool Players::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		lead = NULL;

		bRet = true;
	} while (0);
	return bRet;
}

PlayerUnit* Players::createPlayer(int id, int restMoney)
{
	PlayerUnit* p = PlayerUnit::create();
	p->setId(id);
	p->setRestMoney(restMoney);
	addChild(p);

	return p;
}

PlayerUnit* Players::createAlly(int id, int restMoney)
{
	PlayerUnit* p = createPlayer(id, restMoney);
	allies.insert(id, p);

	return p;
}

PlayerUnit* Players::createEnemy(int id, int restMoney)
{
	PlayerUnit* p = createPlayer(id, restMoney);
	enemies.insert(id, p);

	return p;
}

PlayerUnit* Players::findPlayer(int id)
{
	PlayerUnit* p = allies.at(id);

	if (!p)
		p = enemies.at(id);

	if (!p)
		return NULL;

	return p;
}

bool Players::setLead(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return false;

	lead = p;
	leadIndex = id;
	return true;
}

int Players::changeRestMoney(int delta)
{
	return changeRestMoney(leadIndex, delta);
}
int Players::changeRestMoney(int id, int delta)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->changeRestMoney(delta);
}

int Players::getRestMoney()
{
	return getRestMoney(leadIndex);
}
int Players::getRestMoney(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->getRestMoney();
}

int Players::receiveOneKey()
{
	return receiveOneKey(leadIndex);
}
int Players::receiveOneKey(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->receiveOneKey();
}

int Players::getGainKeys()
{
	return getGainKeys(leadIndex);
}
int Players::getGainKeys(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->getKeys();
}

int Players::useScan()
{
	return useScan(leadIndex);
}
int Players::useScan(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->useScan();
}

int Players::useDig()
{
	return useDig(leadIndex);
}
int Players::useDig(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->useDig();
}

int Players::useDetect()
{
	return useDetect(leadIndex);
}
int Players::useDetect(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->useDetect();
}

int Players::explode()
{
	return explode(leadIndex);
}
int Players::explode(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->explode();
}

int Players::getScanPrice()
{
	return getScanPrice(leadIndex);
}
int Players::getScanPrice(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->getScanPrice();
}

int Players::getDigPrice()
{
	return getDigPrice(leadIndex);
}
int Players::getDigPrice(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->getDigPrice();
}

int Players::getDetectPrice()
{
	return getDetectPrice(leadIndex);
}
int Players::getDetectPrice(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->getDetectPrice();
}

int Players::getBombHurt()
{
	return getBombHurt(leadIndex);
}
int Players::getBombHurt(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->getBombHurt();
}


int Players::getTreasurePrice()
{
	return getTreasurePrice(leadIndex);
}
int Players::getTreasurePrice(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->getTreasurePrice();
}
