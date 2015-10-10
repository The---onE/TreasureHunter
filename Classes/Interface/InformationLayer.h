#pragma once

#include "Global.h"
#include "Data/InformationData.h"
#include "Data/PropData.h"
#include "Data/BlockData.h"
#include "Data/UserData.h"

class InformationLayer : public Layer
{
protected:
	void createLabel(Label* &label, char* text, Color4B color, Point pos, float size);

	Label* restMoneyLabel;
	Label* gameMoneyLabel;
	Label* gainKeysLabel;
	void createRestMoneyLabel();
	void createGameMoneyLabel();
	void createGainKeysLabel();

	Label* scanPriceLabel;
	Label* digPriceLabel;
	Label* detectPriceLabel;
	void createScanPriceLabel();
	void createDigPriceLabel();
	void createDetectPriceLabel();

	Label* goldPriceLabel;
	Label* bombHurtLabel;
	Label* treasurtPriceLabel;
	void createGoldPriceLabel();
	void createBombHurtLabel();
	void createTreasurePriceLabel();

	Label* restKeyLabel;
	Label* restGoldLabel;
	Label* restBombLabel;
	void createRestKeyLabel();
	void createRestGoldLabel();
	void createRestBombLabel();

public:
	CREATE_FUNC(InformationLayer);
	bool init();

	void changeRestMoneyLabel(int rest);
	void changeGameMoneyLabel(int game);
	void changeGainKeysLabel(int keys);

	void changeScanPriceLabel(int price);
	void changeDigPriceLabel(int price);
	void changeDetectPriceLabel(int price);

	void changeGoldPriceLabel(int price);
	void changeBombHurtLabel(int hurt);
	void changeTreasurePriceLabel(int price);

	void changeRestKeyLabel(int rest);
	void changeRestGoldLabel(int rest);
	void changeRestBombLabel(int rest);
};