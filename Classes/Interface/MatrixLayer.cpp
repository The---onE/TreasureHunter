#include "MatrixLayer.h"

bool MatrixLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		initBlocks();
		initSign();

		initBrush();

		drawGuideLine();

		restKey = 0;
		restGold = 0;
		restBomb = 0;

		responseFlag = true;
		signedFlag = false;

		bRet = true;
	} while (0);
	return bRet;
}


void MatrixLayer::onEnter()
{
	do
	{
		Layer::onEnter();

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(false);
		listener->onTouchBegan = CC_CALLBACK_2(MatrixLayer::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(MatrixLayer::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(MatrixLayer::onTouchEnded, this);
		listener->onTouchCancelled = CC_CALLBACK_2(MatrixLayer::onTouchEnded, this);

		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	} while (0);
}

bool MatrixLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (responseFlag)
	{
		Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());

		ERGODIC_BLOCK(i, j)
		{
			if (touchRect[i][j].containsPoint(touchPoint))
			{
				touchLine = i;
				touchRow = j;
				return true;
			}
		}
	}
	
	return false;
}

void MatrixLayer::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void MatrixLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());

	ERGODIC_BLOCK(i, j)
	{
		if (touchRect[i][j].containsPoint(touchPoint))
		{
			if (touchLine == i && touchRow == j)
			{
				signClear();
				signBlock(i, j);
			}
		}
	}
}

void MatrixLayer::initBlocks()
{
	int z = MATRIX_LINE*MATRIX_ROW;
	ERGODIC_BLOCK(i, j) 
	{
		Point center = getCenterByCoord(i, j);
		Point corner = center - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2);
		touchRect[i][j] = Rect(corner.x, corner.y, BLOCK_WIDTH, BLOCK_HEIGHT);

		blocks[i][j] = BlockUnit::create();
		addChild(blocks[i][j], z--);
		blocks[i][j]->initBlock(center);
	}
}

void MatrixLayer::changeBlock(int line, int row, int item, bool visible /* = false */)
{
	blocks[line][row]->changeItem(item, visible);
}

void MatrixLayer::randBlock()
{
	int a[5];
	restKey = a[KEY] = KeyNum;
	a[TREASURE] = TREASURE_NUM;
	restBomb = a[BOMB] = BombNum;
	restGold = a[GOLD] = GoldNum;
	a[NO_ITEM] = BLOCK_NUM - KeyNum - TREASURE_NUM - BombNum - GoldNum;
	srand(time(NULL));

	ERGODIC_BLOCK(i, j)
	{
		int r = randNum(5, a);
		a[r]--;
		blocks[i][j]->changeItem(r);
	}
}

void MatrixLayer::allowResponse()
{
	responseFlag = true;
}

void MatrixLayer::forbiddenResponse()
{
	responseFlag = false;
}

bool MatrixLayer::checkSigned()
{
	return signedFlag;
}

Coord MatrixLayer::getSignedCoord()
{
	if (signedFlag)
	{
		return signedBlock;
	}
	else
	{
		return Coord{ NO_SIGN, NO_SIGN };
	}
}

int MatrixLayer::getSignedItem()
{
	if (signedFlag)
	{
		return blocks[signedBlock.line][signedBlock.row]->getItem();
	}
	else
	{
		return ERROR_ITEM;
	}
}

void MatrixLayer::initBrush()
{
	brush = DrawNode::create();
	this->addChild(brush);
}

void MatrixLayer::drawGuideLine()
{
	brush->clear();

	for (int i = 0; i <= MATRIX_LINE; ++i)
	{
		Point left = Point(MATRIX_LEFT, MATRIX_BOTTOM + BLOCK_HEIGHT*i);
		Point right = Point(MATRIX_RIGHT, MATRIX_BOTTOM + BLOCK_HEIGHT*i);
		brush->drawSegment(left, right, GUIDELINE_WIDTH, GUIDELINE_COLOR);
	}
	for (int i = 0; i <= MATRIX_ROW; ++i)
	{
		Point top = Point(MATRIX_LEFT + BLOCK_WIDTH*i, MATRIX_TOP);
		Point bottom = Point(MATRIX_LEFT + BLOCK_WIDTH*i, MATRIX_BOTTOM);
		brush->drawSegment(top, bottom, GUIDELINE_WIDTH, GUIDELINE_COLOR);
	}
}

int MatrixLayer::signBlock(int line, int row)
{
	signFlag[line][row] = true;
	signSprite[line][row]->setVisible(true);
	signedBlock = Coord{ line, row };
	signedFlag = true;

	return 0;
}

void MatrixLayer::initSign()
{
	ERGODIC_BLOCK(i, j)
	{
		addSprite(signSprite[i][j], MATRIX_SIGN_IMG, getCenterByCoord(i, j), MATRIX_SIGN_SIZE, this);
	}

	signClear();
}

void MatrixLayer::signClear()
{
	ERGODIC_BLOCK(i, j)
	{
		signFlag[i][j] = false;
		signSprite[i][j]->setVisible(false);
	}
	signedFlag = false;
}

void MatrixLayer::dig()
{
	dig(signedBlock);
}

void MatrixLayer::dig(Coord center)
{
	int l = center.line;
	int r = center.row;

	BlockUnit* &b = blocks[l][r];

	int it = b->getItem();
	switch (it)
	{
	case NO_ITEM:
		b->digGetItem();
		break;
	case KEY:
		b->digGetItem();
		restKey--;
		break;
	case TREASURE:
		b->digGetItem();
		break;
	case GOLD:
		b->digGetItem();
		restGold--;
		break;
	case BOMB:
		b->explode();
		restBomb--;
		break;
	default:
		break;
	}
}

void MatrixLayer::scan()
{
	scan(signedBlock);
}

void MatrixLayer::scan(Coord center)
{
	int l = center.line;
	int r = center.row;

	int count = 0;
	for (int i = l - 1; i <= l + 1; ++i)
	{
		if (i >= 0 && i < MATRIX_LINE)
		{
			for (int j = r - 1; j <= r + 1; ++j)
			{
				if (j >= 0 && j < MATRIX_ROW)
				{
					int it = blocks[i][j]->getItem();
					switch (it)
					{
					case KEY:
						count++;
						break;
					case TREASURE:
						blocks[i][j]->showItem(SHOW_ITEM_TIME);
						break;
					case GOLD:
						blocks[i][j]->showItem(SHOW_ITEM_TIME);
						break;
					default:
						break;
					}
				}
			}
		}
	}
	if (blocks[l][r]->getItem() == KEY)
	{
		blocks[l][r]->showItem(SHOW_ITEM_TIME);
	}
	showCount(count, Color4B(KEY_COUNT_R, KEY_COUNT_G, KEY_COUNT_B, KEY_COUNT_A), center, SCAN_STAND_TIME);
	scanAnimate(center);
	Vibrator::vibrate(SCAN_VIBRATE_TIME);
	if (UserDefault::getInstance()->getBoolForKey(EFFECT_STR, EFFECT_DEFAULT_FLAG))
		SimpleAudioEngine::getInstance()->playEffect(SCAN_EFFECT);
	
}

void MatrixLayer::scanAnimate(Coord center)
{
	Sprite* s;
	addSprite(s, SCAN_ANIMATE_IMG, getCenterByCoord(center), SCAN_ANIMATE_SIZE, this);
	s->setOpacity(95);
	auto hide = FadeOut::create(SCAN_ANIMATE_TIME);
	auto rotate = RotateBy::create(SCAN_ANIMATE_TIME, 540);
	auto spawn = Spawn::create(hide, rotate, NULL);
	auto action = Sequence::create(spawn, RemoveSelf::create(), NULL);
	s->runAction(action);
}

void MatrixLayer::detect()
{
	detect(signedBlock);
}

void MatrixLayer::detect(Coord center)
{
	int l = center.line;
	int r = center.row;

	int count = 0;
	for (int i = l - 1; i <= l + 1; ++i)
	{
		if (i >= 0 && i < MATRIX_LINE)
		{
			for (int j = r - 1; j <= r + 1; ++j)
			{
				if (j >= 0 && j < MATRIX_ROW)
				{
					int it = blocks[i][j]->getItem();
					switch (it)
					{
					case BOMB:
						count++;
						break;
					default:
						break;
					}
				}
			}
		}
	}
	if (blocks[l][r]->getItem() == BOMB)
	{
		blocks[l][r]->showItem(SHOW_ITEM_TIME);
	}
	showCount(count, Color4B(BOMB_COUNT_R, BOMB_COUNT_G, BOMB_COUNT_B, BOMB_COUNT_A), center, DETECT_STAND_TIME);
	detectAnimate(center);
	Vibrator::vibrate(DETECT_VIBRATE_TIME);
	if (UserDefault::getInstance()->getBoolForKey(EFFECT_STR, EFFECT_DEFAULT_FLAG))
		SimpleAudioEngine::getInstance()->playEffect(DETECT_EFFECT);
}

void MatrixLayer::detectAnimate(Coord center)
{
	Sprite* s;
	addSprite(s, DETECT_ANIMATE_IMG, getCenterByCoord(center), DETECT_ANIMATE_SIZE, this);
	s->setOpacity(95);
	auto hide = FadeOut::create(DETECT_ANIMATE_TIME);
	auto rotate = RotateBy::create(DETECT_ANIMATE_TIME, 540);
	auto spawn = Spawn::create(hide, rotate, NULL);
	auto action = Sequence::create(spawn, RemoveSelf::create(), NULL);
	s->runAction(action);
}

void MatrixLayer::showCount(int count, Color4B color, Coord center, float time)
{
	char text[32];
	sprintf(text, "%d", count);
	Label* l = Label::createWithTTF(text, COUNT_FONT, COUNT_FONTSIZE);
	l->setTextColor(color);
	l->setPosition(getCenterByCoord(center.line, center.row));
	setSize(l, COUNT_SIZE);
	this->addChild(l, BLOCK_NUM + 1);

	Action* a = Sequence::create(FadeOut::create(time), RemoveSelf::create(), NULL);
	l->runAction(a);
}

void MatrixLayer::showAllItem()
{
	ERGODIC_BLOCK(i, j)
	{
		blocks[i][j]->showItem();
	}
}

void MatrixLayer::showAllItem(float time)
{
	ERGODIC_BLOCK(i, j)
	{
		blocks[i][j]->showItem(time);
	}
}

void MatrixLayer::hideAllItem()
{
	ERGODIC_BLOCK(i, j)
	{
		blocks[i][j]->hideItem();
	}
}

void MatrixLayer::hideAllItem(float time)
{
	ERGODIC_BLOCK(i, j)
	{
		blocks[i][j]->hideItem(time);
	}
}

int MatrixLayer::getRestKey()
{
	return restKey;
}

int MatrixLayer::getRestGold()
{
	return restGold;
}

int MatrixLayer::getRestBomb()
{
	return restBomb;
}