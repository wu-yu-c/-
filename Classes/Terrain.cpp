<<<<<<< Updated upstream
#include "Terrain.h"
#include "MAP.h"
#include "TowerPanleLayer.h"
Terrains* Terrains::createTerrain()
{
	auto terrain = new Terrains();
	if (terrain && terrain->init()) {
		terrain->autorelease();
		return terrain;
	}
	CC_SAFE_DELETE(terrain);
	return NULL;
}

bool Terrains::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	isUpdateMenuShown = false;
	terrain = Sprite::createWithSpriteFrameName("GamePlay/select.png");
	addChild(terrain);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Terrains::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Terrains::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, terrain);
	return true;
}

void Terrains::showUpdateMenu()
{
	auto towerPanleLayer = TowerPanleLayer::create();
	towerPanleLayer->setPosition(this->getPosition());
	towerPanleLayer->setTag(getTag());
	towerPanleLayer->setMyTerrain(this);
	static_cast<MAP*>(this->getParent())->mTouchLayer->addChild(towerPanleLayer);
	towerPanleLayer->inAnimation();
	isUpdateMenuShown = true;
}

void Terrains::hideUpdateMenu()
{
	static_cast<MAP*>(this->getParent())->mTouchLayer->removeChildByTag(getTag());
	isUpdateMenuShown = false;
}

bool Terrains::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void Terrains::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode) && target->isVisible())
	{
		if (isUpdateMenuShown)
		{
			hideUpdateMenu();
		}
		else {
			showUpdateMenu();
		}
	}
	else {
		hideUpdateMenu();
	}
=======
#include "Terrain.h"
#include "MAP.h"
#include "TowerPanleLayer.h"
Terrains* Terrains::createTerrain()
{
	auto terrain = new Terrains();
	if (terrain && terrain->init()) {
		terrain->autorelease();
		return terrain;
	}
	CC_SAFE_DELETE(terrain);
	return NULL;
}

bool Terrains::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	isUpdateMenuShown = false;
	terrain = Sprite::createWithSpriteFrameName("GamePlay/select.png");
	addChild(terrain);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Terrains::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Terrains::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, terrain);
	return true;
}

void Terrains::showUpdateMenu()
{
	auto towerPanleLayer = TowerPanleLayer::create();
	towerPanleLayer->setPosition(this->getPosition());
	towerPanleLayer->setTag(getTag());
	towerPanleLayer->setMyTerrain(this);
	static_cast<MAP*>(this->getParent())->mTouchLayer->addChild(towerPanleLayer);
	towerPanleLayer->inAnimation();
	isUpdateMenuShown = true;
}

void Terrains::hideUpdateMenu()
{
	static_cast<MAP*>(this->getParent())->mTouchLayer->removeChildByTag(getTag());
	isUpdateMenuShown = false;
}

bool Terrains::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void Terrains::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode) && target->isVisible())
	{
		if (isUpdateMenuShown)
		{
			hideUpdateMenu();
		}
		else {
			showUpdateMenu();
		}
	}
	else {
		hideUpdateMenu();
	}
>>>>>>> Stashed changes
}