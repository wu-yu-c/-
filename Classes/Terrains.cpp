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
			bottle->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
			addChild(bottle, 0);
			bottle->addButton();
			bottle->initEvent();
			setTexture("Bottle/Bottle_3.png");
		}
		});

	sunFlowerIcon->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			isBuilt = 1;
			hideTowerPanleLayer();
			auto flower = Flower::create();
			flower->setPosition(Vec2(25, 23));
			addChild(flower, -1);
			setTexture("Flower/level1.png");
		}
		});

	icedStarIcon->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			isBuilt = 1;
			hideTowerPanleLayer();
			auto star = Star::create();
			star->setPosition(Vec2(36, 36));
			addChild(star, 0);
			setTexture("Star/level1_base.png");
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

