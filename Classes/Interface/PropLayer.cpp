#include "PropLayer.h"

bool PropLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		createScan();
		createDig();
		createDetect();

		touchProp = NO_PROP;
		chosenProp = NO_PROP;

		responseFlag = true;
		signedFlag = false;

		bRet = true;
	} while (0);
	return bRet;
}


void PropLayer::onEnter()
{
	do
	{
		Layer::onEnter();

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(false);
		listener->onTouchBegan = CC_CALLBACK_2(PropLayer::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(PropLayer::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(PropLayer::onTouchEnded, this);
		listener->onTouchCancelled = CC_CALLBACK_2(PropLayer::onTouchEnded, this);

		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	} while (0);
}

bool PropLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (responseFlag)
	{
		Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());

		touchProp = NO_PROP;
		if (scanSprite->getBoundingBox().containsPoint(touchPoint))
		{
			touchProp = SCAN;
			return true;
		}
		else if (digSprite->getBoundingBox().containsPoint(touchPoint))
		{
			touchProp = DIG;
			return true;
		}
		else if (detectSprite->getBoundingBox().containsPoint(touchPoint))
		{
			touchProp = DETECT;
			return true;
		}
	}

	return false;
}

void PropLayer::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void PropLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
	deselection();
	switch (touchProp)
	{
	case  SCAN:
		if (scanSprite->getBoundingBox().containsPoint(touchPoint))
		{
			chosenProp = SCAN;
			signProp(SCAN);
		}
		break;
	case DIG:
		if (digSprite->getBoundingBox().containsPoint(touchPoint))
		{
			chosenProp = DIG;
			signProp(DIG);
		}
		break;
	case DETECT:
		if (detectSprite->getBoundingBox().containsPoint(touchPoint))
		{
			chosenProp = DETECT;
			signProp(DETECT);
		}
		break;
	default:
		break;
	}
}

void PropLayer::createScan()
{
	addSprite(scanSprite, SCAN_IMG, SCAN_POSITION, SCAN_SIZE, this);
}

void PropLayer::createDig()
{
	addSprite(digSprite, DIG_IMG, DIG_POSITION, DIG_SIZE, this);
}

void PropLayer::createDetect()
{
	addSprite(detectSprite, DETECT_IMG, DETECT_POSITION, DETECT_SIZE, this);
}

void PropLayer::signProp(int prop)
{
	removeChild(signSprite);

	switch (prop)
	{
	case SCAN:
		addSprite(signSprite, PROP_SIGN_IMG, SCAN_POSITION, PROP_SIGN_SIZE, this);
		break;
	case DIG:
		addSprite(signSprite, PROP_SIGN_IMG, DIG_POSITION, PROP_SIGN_SIZE, this);
		break;
	case DETECT:
		addSprite(signSprite, PROP_SIGN_IMG, DETECT_POSITION, PROP_SIGN_SIZE, this);
		break;
	default:
		break;
	}
}

int PropLayer::getChosenProp()
{
	return chosenProp;
}

void PropLayer::deselection()
{
	chosenProp = NO_PROP;
	signProp(NO_PROP);
}