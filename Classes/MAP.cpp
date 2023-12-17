#include"MAP.h"
USING_NS_CC;
using namespace cocos2d::ui;

MAP* MAP::createScene() {

	MAP* Map = MAP::create();

	Map->mapScene = Scene::create();

	return Map;

}

MAP* SkyMapScene::createMap(){

	auto skymap = MAP::createScene();

	skymap->tilemap = TMXTiledMap::create("MAP/SKY/TileMap1.tmx");
	
	skymap->mapScene->addChild(skymap->tilemap, -1);
	if (skymap->tilemap == nullptr)
		return false;

	skymap->Object = skymap->tilemap->getObjectGroup("Object");

	skymap->InitUI();

	skymap->InitEvent();

	return skymap;

}

MAP* DesertMapScene::createMap() {

	auto desertmap = MAP::createScene();

	desertmap->tilemap = TMXTiledMap::create("MAP/DESERT/TileMap2.tmx");

	desertmap->mapScene->addChild(desertmap->tilemap, -1);
	if (desertmap->tilemap == nullptr)
		return false;

	/*将对象图层中的对象读入Object中*/
	desertmap->Object = desertmap->tilemap->getObjectGroup("Object");

	desertmap->InitUI();

	desertmap->InitEvent();

	return desertmap;

}

bool MAP::InitUI() {

	/*添加菜单按钮*/
	ValueMap menu = Object->getObject("menuButton");               //通过对象名字读取一个object
	float x = menu["x"].asFloat();                                 //获取该对象在地图上的x坐标
	float y = menu["y"].asFloat();                                 //获取该对象在地图上的y坐标

	menuButton = Button::create("MAP/menuButton_normal.png", "MAP/menuButton_pressed.png","");             //创建按钮
	menuButton->setPosition(Vec2(x, y));                           //放到对象位置
	menuButton->setPressedActionEnabled(true);
	mapScene->addChild(menuButton, 1);
	if (menuButton == nullptr)
		return false;


	/*添加暂停按钮*/
	ValueMap stop = Object->getObject("stopButton");
	x = stop["x"].asFloat();
	y = stop["y"].asFloat();

	stopButton = Button::create("MAP/stopButton_normal.png", "MAP/stopButton_pressed.png", "");
	stopButton->setPosition(Vec2(x, y));
	stopButton->setPressedActionEnabled(true);
	mapScene->addChild(stopButton, 1);
	if (stopButton == nullptr)
		return false;

	/*添加怪物出生点*/
	ValueMap birth = Object->getObject("birth");
	x = birth["x"].asFloat();
	y = birth["y"].asFloat();

	birthPlace = Sprite::create("MAP/SKY/birth.png");
	birthPlace->setPosition(x, y);
	mapScene->addChild(birthPlace);
	if (birthPlace == nullptr)
		return false;

	return true;
}

void MAP::InitEvent() {

	/*初始化菜单按钮*/
	menuButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {

			auto choosemenu = ChooseMenu::createLayer();
			mapScene->addChild(choosemenu);

		}
		});



}

Layer* ChooseMenu::createLayer() {
	return ChooseMenu::create();
}

bool ChooseMenu::init() {
	if (!Layer::init())
		return false;

	InitUI();

	InitEvent();

	return true;
}

bool ChooseMenu::InitUI() {

	/*添加菜单背景*/
	Sprite* choosemenu = Sprite::create("MAP/Menu.png");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	choosemenu->setPosition(Vec2(origin.x + 568, origin.y + 320));
	this->addChild(choosemenu, 1);
	if (choosemenu == nullptr)
		return false;

	/*添加继续游戏按钮*/
	continueButton = Button::create("MAP/continueBUtton_normal.png", "MAP/continueButton_pressed.png");
	continueButton->setPosition(Vec2(origin.x + 565, origin.y + 395));
	this->addChild(continueButton, 2);
	if (continueButton == nullptr)
		return false;

	/*添加重新开始按钮*/
	restartButton = Button::create("MAP/restartButton_normal.png", "MAP/restartButton_pressed.png");
	restartButton->setPosition(Vec2(origin.x + 560, origin.y + 325));
	this->addChild(restartButton, 2);
	if (restartButton == nullptr)
		return false;

	/*添加选择关卡按钮*/
	returnButton = Button::create("MAP/returnButton_normal.png", "MAP/returnButton_pressed.png");
	returnButton->setPosition(Vec2(origin.x + 558, origin.y + 255));
	this->addChild(returnButton, 2);
	if (returnButton == nullptr)
		return false;

	return true;
}

void ChooseMenu::InitEvent() {
	//目前全部设置为返回
	/*设置继续游戏按钮*/
	continueButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {

			Director::getInstance()->popScene();
			
		}
		});

	/*设置重新开始按钮*/
	restartButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {

			Director::getInstance()->popScene();

		}
		});

	/*设置返回按钮*/
	returnButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {

			Director::getInstance()->popScene();

		}
		});

}