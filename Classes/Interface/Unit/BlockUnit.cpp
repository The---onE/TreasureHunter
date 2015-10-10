#include "BlockUnit.h"

bool BlockUnit::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		item = NO_ITEM;
		itemSprite = NULL;
		visibleFlag = false;

		bRet = true;
	} while (0);
	return bRet;
}

void BlockUnit::initBlock(Point pos)
{
	this->setPosition(pos);
}

void BlockUnit::changeItem(int it, bool visible /* = false */)
{
	item = it;
	if (it == PIT)
		visible = true;
	if (visible)
	{
		switch (it)
		{
		case NO_ITEM:
			break;
		case PIT:
			changeItem(PIT_IMG, PIS_SIZE, false);
			showItem(SHOW_DIG_TIME);
			break;
		case KEY:
			changeItem(KEY_IMG, KEY_SIZE, false);
			showItem(SHOW_ITEM_TIME);
			break;
		case TREASURE:
			changeItem(TREASURE_IMG, TREASURE_SIZE, false);
			showItem(SHOW_ITEM_TIME);
			break;
		case BOMB:
			changeItem(BOMB_IMG, BOMB_SIZE, false);
			showItem(SHOW_ITEM_TIME);
			break;
		case GOLD:
			changeItem(GOLD_IMG, GOLD_SIZE, false);
			showItem(SHOW_ITEM_TIME);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (it)
		{
		case NO_ITEM:
			break;
		case PIT:
			changeItem(PIT_IMG, PIS_SIZE, false);
			break;
		case KEY:
			changeItem(KEY_IMG, KEY_SIZE, false);
			break;
		case TREASURE:
			changeItem(TREASURE_IMG, TREASURE_SIZE, false);
			break;
		case BOMB:
			changeItem(BOMB_IMG, BOMB_SIZE, false);
			break;
		case GOLD:
			changeItem(GOLD_IMG, GOLD_SIZE, false);
			break;
		default:
			break;
		}
	}
}

void BlockUnit::changeItem(string s, float size, bool visible /* = false */)
{
	removeChild(itemSprite);

	addSprite(itemSprite, s, Point::ZERO, size, this);
	itemSprite->setVisible(visible);
	visibleFlag = visible;
}

void BlockUnit::showItem()
{
	if (itemSprite)
	{
		itemSprite->setVisible(true);
		itemSprite->setOpacity(255);
		visibleFlag = true;
	}
}

void BlockUnit::showItem(float time)
{
	if (itemSprite)
	{
		if (!visibleFlag)
		{
			itemSprite->setVisible(true);
			visibleFlag = true;
			itemSprite->setOpacity(0);
			auto* show = FadeIn::create(time);
			itemSprite->runAction(show);
		}
	}
}

void BlockUnit::hideItem()
{
	if (item == PIT)
		return;
	if (itemSprite)
	{
		itemSprite->setVisible(false);
		itemSprite->setOpacity(0);
		visibleFlag = false;
	}
}

void BlockUnit::hideItem(float time)
{
	if (item == PIT)
		return;
	if (itemSprite)
	{
		if (visibleFlag)
		{
			visibleFlag = false;
			//itemSprite->setOpacity(255);
			auto* hide = FadeOut::create(time);
			itemSprite->runAction(hide);
		}
	}
}

void BlockUnit::showDigItem(float time)
{
	Sprite* s;
	string img;
	float size;
	switch (item)
	{
	case KEY:
		img = KEY_IMG;
		size = KEY_SIZE;
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_STR, EFFECT_DEFAULT_FLAG))
			SimpleAudioEngine::getInstance()->playEffect(KEY_EFFECT);
		break;
	case TREASURE:
		img = TREASURE_IMG;
		size = TREASURE_SIZE;
		break;
	case GOLD:
		img = GOLD_IMG;
		size = GOLD_SIZE;
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_STR, EFFECT_DEFAULT_FLAG))
			SimpleAudioEngine::getInstance()->playEffect(GOLD_EFFECT);
		break;
	case NO_ITEM:
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_STR, EFFECT_DEFAULT_FLAG))
			SimpleAudioEngine::getInstance()->playEffect(DIG_EFFECT);
		return;
		break;
	case BOMB:
	case PIT:
	default:
		return;
		break;
	}
	addSprite(s, img, Point::ZERO, size, this, 1);
	auto move = MoveBy::create(time, Point(0, BLOCK_HEIGHT));
	s->setOpacity(63);
	auto show = FadeIn::create(time * 3 / 4);
	auto hide = FadeOut::create(time / 4);
	auto sh = Sequence::create(show, hide, NULL);
	auto spawn = Spawn::create(move, sh, NULL);
	auto action = Sequence::create(spawn, RemoveSelf::create(), NULL);
	s->runAction(action);
}

void BlockUnit::digGetItem()
{
	showDigItem(SHOW_DIG_TIME);
	changeItem(PIT);
	Vibrator::vibrate(DIG_VIBRATE_TIME);
}

void BlockUnit::explode()
{
	Sprite* s;
	addSprite(s, EXPLODE_IMG, Point::ZERO, 0, this, 1);
	s->setOpacity(63);
	auto zoom = ScaleTo::create(EXPLODE_TIME / 6, DATUM*EXPLODE_SIZE / s->getContentSize().height);
	auto show = FadeIn::create(EXPLODE_TIME / 6);
	auto spawn = Spawn::create(zoom, show, NULL);
	auto hide = FadeOut::create(EXPLODE_TIME * 5 / 5);
	auto action = Sequence::create(spawn, hide, RemoveSelf::create(), NULL);
	s->runAction(action);
	changeItem(PIT);
	Vibrator::vibrate(EXPLODE_VIBRATE_TIME);
	if (UserDefault::getInstance()->getBoolForKey(EFFECT_STR, EFFECT_DEFAULT_FLAG))
		SimpleAudioEngine::getInstance()->playEffect(EXPLODE_EFFECT);
}

int BlockUnit::getItem()
{
	return item;
}