<<<<<<< Updated upstream
#include "TouchLayer.h"
void TouchLayer::setTouchShield()
{
	touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
	touchlistener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	touchlistener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
	touchlistener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithFixedPriority(touchlistener, -1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);
}

void TouchLayer::removeTouchShield()
{
	if (touchlistener != NULL)
		_eventDispatcher->removeEventListener(touchlistener);
}

bool TouchLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	winSize = Director::getInstance()->getWinSize();
	SpriteFrame* frame = NULL;
	
	isFlag = false;
	setTouchShield();

	return true;
=======
#include "TouchLayer.h"
void TouchLayer::setTouchShield()
{
	touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
	touchlistener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	touchlistener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
	touchlistener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithFixedPriority(touchlistener, -1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);
}

void TouchLayer::removeTouchShield()
{
	if (touchlistener != NULL)
		_eventDispatcher->removeEventListener(touchlistener);
}

bool TouchLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	winSize = Director::getInstance()->getWinSize();
	SpriteFrame* frame = NULL;
	
	isFlag = false;
	setTouchShield();

	return true;
>>>>>>> Stashed changes
}