#include "InformationLayer.h"

bool InformationLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		createRestMoneyLabel();
		createGameMoneyLabel();
		createGainKeysLabel();

		createScanPriceLabel();
		createDigPriceLabel();
		createDetectPriceLabel();

		createGoldPriceLabel();
		createBombHurtLabel();
		createTreasurePriceLabel();

		createRestKeyLabel();
		createRestGoldLabel();
		createRestBombLabel();

		bRet = true;
	} while (0);
	return bRet;
}

void InformationLayer::createLabel(Label* &label, char* text, Color4B color, Point pos, float size)
{
	label = Label::createWithTTF(text, INFORMATION_FONT, INFORMATION_FONTSIZE);
	label->setTextColor(color);
	label->enableShadow(Color4B::BLACK, INFORMATION_SHADOW_OFFSET);
	label->setPosition(pos);
	setSize(label, size);
	addChild(label);
}

void InformationLayer::createRestMoneyLabel()
{
	char text[32];
	sprintf(text, "Rest Money: $0");
	createLabel(restMoneyLabel, text, Color4B(REST_MONEY_R, REST_MONEY_G, REST_MONEY_B, REST_MONEY_A), REST_MONEY_POSITION, REST_MONEY_SIZE);
}
void InformationLayer::createGameMoneyLabel()
{
	char text[32];
	sprintf(text, "Game Money: $0");
	createLabel(gameMoneyLabel, text, Color4B(GAME_MONEY_R, GAME_MONEY_G, GAME_MONEY_B, GAME_MONEY_A), GAME_MONEY_POSITION, GAME_MONEY_SIZE);
}
void InformationLayer::createGainKeysLabel()
{
	char text[32];
	sprintf(text, "Keys: 0");
	createLabel(gainKeysLabel, text, Color4B(GAIN_KEYS_R, GAIN_KEYS_G, GAIN_KEYS_B, GAIN_KEYS_A), GAIN_KEYS_POSITION, GAIN_KEYS_SIZE);
}
void InformationLayer::createScanPriceLabel()
{
	char text[32];
	sprintf(text, "$0");
	createLabel(scanPriceLabel, text, Color4B(SCAN_PRICE_R, SCAN_PRICE_G, SCAN_PRICE_B, SCAN_PRICE_A), SCAN_POSITION + PRICE_OFFSET, PRICE_SIZE);
}
void InformationLayer::createDigPriceLabel()
{
	char text[32];
	sprintf(text, "$0");
	createLabel(digPriceLabel, text, Color4B(DIG_PRICE_R, DIG_PRICE_G, DIG_PRICE_B, DIG_PRICE_A), DIG_POSITION + PRICE_OFFSET, PRICE_SIZE);
}
void InformationLayer::createDetectPriceLabel()
{
	char text[32];
	sprintf(text, "$0");
	createLabel(detectPriceLabel, text, Color4B(DETECT_PRICE_R, DETECT_PRICE_G, DETECT_PRICE_B, DETECT_PRICE_A), DETECT_POSITION + PRICE_OFFSET, PRICE_SIZE);
}
void InformationLayer::createGoldPriceLabel()
{
	char text[32];
	sprintf(text, "Gold Price:$0");
	createLabel(goldPriceLabel, text, Color4B(GOLD_PRICE_R, GOLD_PRICE_G, GOLD_PRICE_B, GOLD_PRICE_A), GOLD_PRICE_POSITION, GOLD_PRICE_SIZE);
}
void InformationLayer::createBombHurtLabel()
{
	char text[32];
	sprintf(text, "Bomb Hurt:$0");
	createLabel(bombHurtLabel, text, Color4B(BOMB_HURT_R, BOMB_HURT_G, BOMB_HURT_B, BOMB_HURT_A), BOMB_HURT_POSITION, BOMB_HURT_SIZE);
}
void InformationLayer::createTreasurePriceLabel()
{
	char text[128];
	sprintf(text, "Now You Could Get $0\nIf You Dig The Treasure!");
	createLabel(treasurtPriceLabel, text, Color4B(TREASURE_PRICE_R, TREASURE_PRICE_G, TREASURE_PRICE_B, TREASURE_PRICE_A), TREASURE_PRICE_POSITION, TREASURE_PRICE_SIZE);
}
void InformationLayer::createRestKeyLabel()
{
	char text[32];
	sprintf(text, "Rest Key:0");
	createLabel(restKeyLabel, text, Color4B(REST_KEY_R, REST_KEY_G, REST_KEY_B, REST_KEY_A), REST_KEY_POSITION, REST_KEY_SIZE);
}
void InformationLayer::createRestGoldLabel()
{
	char text[32];
	sprintf(text, "Rest Gold:0");
	createLabel(restGoldLabel, text, Color4B(REST_GOLD_R, REST_GOLD_G, REST_GOLD_B, REST_GOLD_A), REST_GOLD_POSITION, REST_GOLD_SIZE);
}
void InformationLayer::createRestBombLabel()
{
	char text[32];
	sprintf(text, "Rest Bomb:0");
	createLabel(restBombLabel, text, Color4B(REST_BOMB_R, REST_BOMB_G, REST_BOMB_B, REST_BOMB_A), REST_BOMB_POSITION, REST_BOMB_SIZE);
}

void InformationLayer::changeRestMoneyLabel(int rest)
{
	char text[32];
	sprintf(text, "Rest Money: $%d", rest);
	restMoneyLabel->setString(text);
}

void InformationLayer::changeGameMoneyLabel(int game)
{
	char text[32];
	sprintf(text, "Game Money: $%d", game);
	gameMoneyLabel->setString(text);
}

void InformationLayer::changeGainKeysLabel(int keys)
{
	char text[32];
	sprintf(text, "Gain Keys: %d", keys);
	gainKeysLabel->setString(text);
}

void InformationLayer::changeScanPriceLabel(int price)
{
	char text[32];
	sprintf(text, "$%d", price);
	scanPriceLabel->setString(text);
}

void InformationLayer::changeDigPriceLabel(int price)
{
	char text[32];
	sprintf(text, "$%d", price);
	digPriceLabel->setString(text);
}

void InformationLayer::changeDetectPriceLabel(int price)
{
	char text[32];
	sprintf(text, "$%d", price);
	detectPriceLabel->setString(text);
}

void InformationLayer::changeGoldPriceLabel(int price)
{
	char text[128];
	sprintf(text, "Gold Price:$%d", price);
	goldPriceLabel->setString(text);
}

void InformationLayer::changeBombHurtLabel(int hurt)
{
	char text[128];
	sprintf(text, "Bomb Hurt:$%d", hurt);
	bombHurtLabel->setString(text);
}

void InformationLayer::changeTreasurePriceLabel(int price)
{
	char text[128];
	sprintf(text, "Now You Could Get $%d\nIf You Dig The Treasure!", price);
	treasurtPriceLabel->setString(text);
}

void InformationLayer::changeRestKeyLabel(int rest)
{
	char text[32];
	sprintf(text, "Rest Key:%d", rest);
	restKeyLabel->setString(text);
}

void InformationLayer::changeRestGoldLabel(int rest)
{
	char text[32];
	sprintf(text, "Rest Gold:%d", rest);
	restGoldLabel->setString(text);
}

void InformationLayer::changeRestBombLabel(int rest)
{
	char text[32];
	sprintf(text, "Rest Bomb:%d", rest);
	restBombLabel->setString(text);
}
