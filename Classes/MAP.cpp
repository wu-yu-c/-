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

	/*������ͼ���еĶ������Object��*/
	desertmap->Object = desertmap->tilemap->getObjectGroup("Object");

	desertmap->InitUI();

	desertmap->InitEvent();

	return desertmap;

}

bool MAP::InitUI() {

	/*��Ӳ˵���ť*/
	ValueMap menu = Object->getObject("menuButton");               //ͨ���������ֶ�ȡһ��object
	float x = menu["x"].asFloat();                                 //��ȡ�ö����ڵ�ͼ�ϵ�x����
	float y = menu["y"].asFloat();                                 //��ȡ�ö����ڵ�ͼ�ϵ�y����

	menuButton = Button::create("MAP/menuButton_normal.png", "MAP/menuButton_pressed.png","");             //������ť
	menuButton->setPosition(Vec2(x, y));                           //�ŵ�����λ��
	menuButton->setPressedActionEnabled(true);
	mapScene->addChild(menuButton, 1);
	if (menuButton == nullptr)
		return false;


	/*�����ͣ��ť*/
	ValueMap stop = Object->getObject("stopButton");
	x = stop["x"].asFloat();
	y = stop["y"].asFloat();

	stopButton = Button::create("MAP/stopButton_normal.png", "MAP/stopButton_pressed.png", "");
	stopButton->setPosition(Vec2(x, y));
	stopButton->setPressedActionEnabled(true);
	mapScene->addChild(stopButton, 1);
	if (stopButton == nullptr)
		return false;

	/*��ӹ��������*/
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

	/*��ʼ���˵���ť*/
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

	/*��Ӳ˵�����*/
	Sprite* choosemenu = Sprite::create("MAP/Menu.png");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	choosemenu->setPosition(Vec2(origin.x + 568, origin.y + 320));
	this->addChild(choosemenu, 1);
	if (choosemenu == nullptr)
		return false;

	/*��Ӽ�����Ϸ��ť*/
	continueButton = Button::create("MAP/continueBUtton_normal.png", "MAP/continueButton_pressed.png");
	continueButton->setPosition(Vec2(origin.x + 565, origin.y + 395));
	this->addChild(continueButton, 2);
	if (continueButton == nullptr)
		return false;

	/*������¿�ʼ��ť*/
	restartButton = Button::create("MAP/restartButton_normal.png", "MAP/restartButton_pressed.png");
	restartButton->setPosition(Vec2(origin.x + 560, origin.y + 325));
	this->addChild(restartButton, 2);
	if (restartButton == nullptr)
		return false;

	/*���ѡ��ؿ���ť*/
	returnButton = Button::create("MAP/returnButton_normal.png", "MAP/returnButton_pressed.png");
	returnButton->setPosition(Vec2(origin.x + 558, origin.y + 255));
	this->addChild(returnButton, 2);
	if (returnButton == nullptr)
		return false;

	return true;
}

void ChooseMenu::InitEvent() {
	//Ŀǰȫ������Ϊ����
	/*���ü�����Ϸ��ť*/
	continueButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {

			Director::getInstance()->popScene();
			
		}
		});

	/*�������¿�ʼ��ť*/
	restartButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {

			Director::getInstance()->popScene();

		}
		});

	/*���÷��ذ�ť*/
	returnButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {

			Director::getInstance()->popScene();

		}
		});

}