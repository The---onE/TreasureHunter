#pragma once

#include "Global.h"
#include "Unit/BlockUnit.h"
#include "Data/MatrixData.h"
#include "Data/UserData.h"

class MatrixLayer : public Layer
{
protected:
	BlockUnit* blocks[MATRIX_LINE][MATRIX_ROW];
	Rect touchRect[MATRIX_LINE][MATRIX_ROW];
	bool signFlag[MATRIX_LINE][MATRIX_ROW];
	Sprite* signSprite[MATRIX_LINE][MATRIX_ROW];

	DrawNode* brush;

	int touchLine, touchRow;
	Coord signedBlock;

	int restKey;
	int restGold;
	int restBomb;

	bool responseFlag;
	bool signedFlag;

public:
	CREATE_FUNC(MatrixLayer);
	bool init();
	void onEnter();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	void initBlocks();
	void changeBlock(int line, int row, int item, bool visible = false);
	void randBlock();

	void allowResponse();
	void forbiddenResponse();
	bool checkSigned();
	Coord getSignedCoord();
	int getSignedItem();

	void initBrush();
	void drawGuideLine();

	void initSign();
	void signClear();
	int signBlock(int line, int row);

	void dig();
	void dig(Coord center);

	void scan();
	void scan(Coord center);
	void scanAnimate(Coord center);

	void detect();
	void detect(Coord center);
	void detectAnimate(Coord center);

	void showCount(int count, Color4B color, Coord center, float time);

	void showAllItem();
	void showAllItem(float time);
	void hideAllItem();
	void hideAllItem(float time);

	int getRestKey();
	int getRestGold();
	int getRestBomb();
};