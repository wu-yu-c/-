#include "Terrains.h"
#include "MAP.h"
#include "cocos2d.h"
#include "Tower.h"
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

	initUI();

	initEvent();
	return true;
}
void Terrains::initUI()
{
	//auto nowObject = Director::getInstance()->getRunningScene()->getChildByTag(getTag());
	//auto nowPosition = this->getPosition();

	bottleIcon = Button::create("Bottle/Bottle01.png", "Bottle/Bottle01.png", "");
	bottleIcon->setPosition(Vec2(-70, 70));
	bottleIcon->setPressedActionEnabled(true);
	bottleIcon->setVisible(false);
	this->addChild(bottleIcon, 2);

	sunFlowerIcon = Button::create("Flower/Flower01.png", "Flower/Flower01.png", "");
	sunFlowerIcon->setPosition(Vec2(0, 70));
	sunFlowerIcon->setPressedActionEnabled(true);
	sunFlowerIcon->setVisible(false);
	this->addChild(sunFlowerIcon, 2);

	icedStarIcon = Button::create("Star/Star01.png", "Star/Star01.png", "");
	icedStarIcon->setPosition(Vec2(70, 70));
	icedStarIcon->setPressedActionEnabled(true);
	icedStarIcon->setVisible(false);
	this->addChild(icedStarIcon, 2);

	isTowerPanleLayerShown = false;
}

void Terrains::initEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Terrains::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Terrains::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, terrain);

	bottleIcon->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto nowScene = Director::getInstance()->getRunningScene();
			auto nowTerrain = nowScene->getChildByTag(getTag());
			auto bottle = Bottle::createBottleTower(this->getTag());
			bottle->setTag(nowTerrain->getTag());
			nowTerrain->removeFromParent();
			nowScene->addChild(bottle, 0);
		}
		});

	sunFlowerIcon->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto nowScene = Director::getInstance()->getRunningScene();
			auto nowTerrain = nowScene->getChildByTag(getTag());
			auto flower = Flower::createFlowerTower(this->getTag());
			flower->setTag(nowTerrain->getTag());
			nowTerrain->removeFromParent();
			nowScene->addChild(flower, 0);
		}
		});

	icedStarIcon->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto nowScene = Director::getInstance()->getRunningScene();
			auto nowTerrain = nowScene->getChildByTag(getTag());
			auto star = Star::createStarTower(this->getTag());
			star->setTag(nowTerrain->getTag());
			nowTerrain->removeFromParent();
			nowScene->addChild(star, 0);
		}
		});
}

void Terrains::showTowerPanleLayer()
{
	if (isTowerPanleLayerShown == false) {
		isTowerPanleLayerShown = true;

		bottleIcon->setVisible(true);
		sunFlowerIcon->setVisible(true);
		icedStarIcon->setVisible(true);
	}
	//towerPanleLayer->setMyTerrain(this);
	//Director::getInstance()->getRunningScene()->addChild(towerPanleLayer);
	//towerPanleLayer->inAnimation();
}

//void Terrains::hideTowerPanleLayer()
//{
//	if (isTowerPanleLayerShown) {
//		static_cast<MAP*>(this->getParent())->removeChildByTag(getTag());
//		isTowerPanleLayerShown = false;
//	}
//}
void Terrains::hideTowerPanleLayer()
{
	if (isTowerPanleLayerShown) {
		isTowerPanleLayerShown = false;

		bottleIcon->setVisible(false);
		sunFlowerIcon->setVisible(false);
		icedStarIcon->setVisible(false);
	}
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
		if (isTowerPanleLayerShown)
			hideTowerPanleLayer();
		else
			showTowerPanleLayer();
	}
	else {
		hideTowerPanleLayer();
	}
}