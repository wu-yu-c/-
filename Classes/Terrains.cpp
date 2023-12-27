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
	isShow = false;
	isBuilt = false;
	setTexture("GamePlay/select.png");
	setOpacity(0);

	initUI();

	initEvent();
	return true;
}
void Terrains::initUI()
{
	bottleIcon = Button::create("Bottle/Bottle01.png", "Bottle/Bottle01.png", "");
	bottleIcon->setPosition(Vec2(-30, 110));
	bottleIcon->setPressedActionEnabled(true);
	bottleIcon->setVisible(false);
	this->addChild(bottleIcon, 2);

	sunFlowerIcon = Button::create("Flower/Flower01.png", "Flower/Flower01.png", "");
	sunFlowerIcon->setPosition(Vec2(40, 110));
	sunFlowerIcon->setPressedActionEnabled(true);
	sunFlowerIcon->setVisible(false);
	this->addChild(sunFlowerIcon, 2);

	icedStarIcon = Button::create("Star/Star01.png", "Star/Star01.png", "");
	icedStarIcon->setPosition(Vec2(110, 110));
	icedStarIcon->setPressedActionEnabled(true);
	icedStarIcon->setVisible(false);
	this->addChild(icedStarIcon, 2);

}

void Terrains::initEvent()
{
	bottleIcon->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			isBuilt = 1;
			hideTowerPanleLayer();
			auto bottle = Bottle::create();
			bottle->setName("bottle");
			bottle->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
			addChild(bottle, 0);
			setTexture("Bottle/Bottle_3.png");
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
	if (isShow == false) {
		isShow = true;
		setOpacity(255);
		bottleIcon->setVisible(true);
		sunFlowerIcon->setVisible(true);
		icedStarIcon->setVisible(true);
	}
}

void Terrains::hideTowerPanleLayer()
{
	if (isShow) {
		isShow = false;
		if (!isBuilt)
			setOpacity(0);
		bottleIcon->setVisible(false);
		sunFlowerIcon->setVisible(false);
		icedStarIcon->setVisible(false);
	}
}

