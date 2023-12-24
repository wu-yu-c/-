<<<<<<< Updated upstream
#pragma once
#include "cocos2d.h"
USING_NS_CC;
class TouchLayer :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(TouchLayer);
	EventListenerTouchOneByOne* listener;
	EventListenerTouchOneByOne* touchlistener;
	bool isFlag;
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void removeTouchShield();
	void setTouchShield();
	Size winSize;
=======
#pragma once
#include "cocos2d.h"
USING_NS_CC;
class TouchLayer :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(TouchLayer);
	EventListenerTouchOneByOne* listener;
	EventListenerTouchOneByOne* touchlistener;
	bool isFlag;
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void removeTouchShield();
	void setTouchShield();
	Size winSize;
>>>>>>> Stashed changes
};