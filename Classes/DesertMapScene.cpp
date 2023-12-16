#include"DesertMapScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* DesertMapScene::createScene() {

	return DesertMapScene::create();

}

bool DesertMapScene::init() {

	if (!Scene::init())
		return false;


	desertMap = TMXTiledMap::create("MAP/DESERT/TileMap2.tmx");
	
	this->addChild(desertMap, -1);
	Object = desertMap->getObjectGroup("Object");

	InitUI();

	InitEvent();

	return true;

}

bool DesertMapScene::InitUI() {

	/*��Ӳ˵���ť*/
	ValueMap menu = Object->getObject("menuButton");
	float x = menu["x"].asFloat();
	float y = menu["y"].asFloat();

	menuButton = Button::create("MAP/menuButton_normal.png", "MAP/menuButton_pressed.png", "");
	menuButton->setPosition(Vec2(x, y));
	menuButton->setPressedActionEnabled(true);
	addChild(menuButton, 1);
	if (menuButton == nullptr)
		return false;


	/*�����ͣ��ť*/
	ValueMap stop = Object->getObject("stopButton");
	x = stop["x"].asFloat();
	y = stop["y"].asFloat();

	stopButton = Button::create("MAP/stopButton_normal.png", "MAP/stopButton_pressed.png", "");
	stopButton->setPosition(Vec2(x, y));
	stopButton->setPressedActionEnabled(true);
	addChild(stopButton, 1);
	if (stopButton == nullptr)
		return false;


	return true;
}

void DesertMapScene::InitEvent() {

	/*��ʼ���˵���ť*/
	menuButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {

			auto choosemenu = ChooseMenu::createLayer();
			this->addChild(choosemenu);

		}
		});
}