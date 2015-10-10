#pragma once

#include "Global.h"

#include "Data/BlockData.h"
#include "Data/MatrixData.h"
#include "Data/PropData.h"
#include "Data/SettingData.h"

class BlockUnit : public Node
{
protected:
	int item;
	Sprite* itemSprite;
	bool visibleFlag;

	Point position;

public:
	CREATE_FUNC(BlockUnit);
	bool init();

	void initBlock(Point pos);
	void changeItem(int it, bool visible = false);
	void changeItem(string s, float size, bool visible = false);

	void showItem();
	void showItem(float time);
	void hideItem();
	void hideItem(float time);

	void showDigItem(float time);
	void digGetItem();
	void explode();

	int getItem();
};