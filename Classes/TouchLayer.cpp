#include "TouchLayer.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Tower.h"
#include "MAP.h"
#include <vector>
USING_NS_CC;
using namespace cocos2d::ui;
TouchLayer* TouchLayer::createTouchLayer()
{
	return TouchLayer::create();
}

bool TouchLayer::init()
{
	if (!Layer::init())
		return false;
	initEvent();
	return true;
}

void TouchLayer::initEvent()
{
	touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
	touchlistener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	touchlistener->setSwallowTouches(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener,this);
}

void TouchLayer::addWrongPlace(Point location)
{
	auto wrong = Sprite::create("GamePlay/warning.png");
	wrong->setPosition(location);
	wrong->runAction(Sequence::create(FadeOut::create(0.6f)
		, CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, wrong))
		, NULL));
	addChild(wrong);
}

bool TouchLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void TouchLayer::onTouchEnded(Touch* touch, Event* event)
{
	bool isRightPlace = 0;
	auto map = static_cast<MAP*>(Director::getInstance()->getRunningScene());
	Point pos = touch->getLocation();//�õ�����λ��
	for (size_t i = 0; i < map->terrain.size(); i++) {
		auto element = map->terrain[i];
		//��������ʾ��Ϣ��������
		if (element->isShow) {
			//��û�н����������ؽ����˵�
			if (!element->isBuilt)
				element->hideTowerPanleLayer();
			//������������������������Ϣ
			else
				element->hideTowerInfo();
			return;
		}
	}
	for (size_t i = 0; i < map->terrain.size(); i++) {
		auto element = map->terrain[i];
		Rect rect = element->getBoundingBox();
		if (rect.containsPoint(pos))
		{
			if (!element->isBuilt)
				element->showTowerPanleLayer();
			else
				element->showTowerInfo();
			isRightPlace = 1;
			break;
		}
	}
	if (!isRightPlace)
		addWrongPlace(pos);
}