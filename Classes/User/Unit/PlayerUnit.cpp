#include "PlayerUnit.h"

bool PlayerUnit::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		keys = 0;
		initPrice();

		bRet = true;
	} while (0);
	return bRet;
}

void PlayerUnit::initPrice()
{
	scanPrice = ScanBasePrice;
	digPrice = DigBasePrice;
	detectPrice = DetectBasePrice;

	bombHurt = BombBaseHurt;
}

int PlayerUnit::receiveOneKey()
{
	keys++;
	return keys;
}

int PlayerUnit::getKeys()
{
	return keys;
}

void PlayerUnit::setId(int i)
{
	id = i;
}

void PlayerUnit::setRestMoney(int rest)
{
	restMoney = rest;
}

int PlayerUnit::getRestMoney()
{
	return restMoney;
}

int PlayerUnit::changeRestMoney(int delta)
{
	restMoney += delta;
	return restMoney;
}

int PlayerUnit::useScan()
{
	int sp = scanPrice;
	int rm = restMoney - scanPrice;
	if (rm >= 0)
	{
		restMoney = rm;
	}
	else
	{
		return -1;
	}
	scanPrice *= ScanIncreaseCoefficient;

	return sp;
}

int PlayerUnit::useDig()
{
	int dp = digPrice;
	int rm = restMoney - digPrice;
	if (rm >= 0)
	{
		restMoney = rm;
	}
	else
	{
		return -1;
	}
	digPrice *= DigIncreaseCoefficient;

	return dp;
}

int PlayerUnit::useDetect()
{
	int dp = detectPrice;
	int rm = restMoney - detectPrice;
	if (rm >= 0)
	{
		restMoney = rm;
	}
	else
	{
		return -1;
	}
	detectPrice *= DetectIncreaseCoefficient;

	return dp;
}

int PlayerUnit::explode()
{
	int sh = bombHurt;
	restMoney -= bombHurt;
	bombHurt *= HurtIncreaseCoefficient;

	return sh;
}

int PlayerUnit::getScanPrice()
{
	return scanPrice;
}

int PlayerUnit::getDigPrice()
{
	return digPrice;
}

int PlayerUnit::getDetectPrice()
{
	return detectPrice;
}

int PlayerUnit::getBombHurt()
{
	return bombHurt;
}

int PlayerUnit::getTreasurePrice()
{
	if (keys > 0)
	{
		int price = TreasureBasePrice;
		for (int i = 0; i < keys - 1; ++i)
			price *= TreasureIncreaseCoefficient;
		return price;
	}
	else
	{
		return 0;
	}
}