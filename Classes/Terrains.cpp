#include "Terrains.h"
#include "MAP.h"
#include "TowerPanleLayer.h"
#include "cocos2d.h"
using namespace cocos2d::ui;
Terrains* Terrains::createTerrain()
{
	return  Terrains::create();
}

bool Terrains::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	isTowerPanleLayerShown = false;
	terrain = Sprite::create("GamePlay/select.png");
	addChild(terrain);

	initEvent();
	return true;
}

void Terrains::initEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Terrains::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Terrains::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, terrain);
}

void Terrains::showTowerPanleLayer()
{
	isTowerPanleLayerShown = true;
	auto nowObject = Director::getInstance()->getRunningScene()->getChildByTag(getTag());
	//auto nowPosition = this->getPosition();
	
	bottleIcon = Button::create("GamePlay/Bottle/Bottle01.png", "GamePlay/Bottle/Bottle01.png", "");
	bottleIcon->setPosition(Vec2(0,0));
	bottleIcon->setPressedActionEnabled(true);
	this->addChild(bottleIcon, 1);

	//towerPanleLayer->setMyTerrain(this);
	//Director::getInstance()->getRunningScene()->addChild(towerPanleLayer);
	//towerPanleLayer->inAnimation();
}

void Terrains::hideTowerPanleLayer()
{
	static_cast<MAP*>(this->getParent())->removeChildByTag(123);
	isTowerPanleLayerShown = false;
}

bool Terrains::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void Terrains::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());//取当前点击的加号

	Point locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode) && target->isVisible())
	{
		showTowerPanleLayer();
	}
	else {
		hideTowerPanleLayer();
	}
}