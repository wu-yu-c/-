#include"SkyMapScene.h"
USING_NS_CC;
using namespace cocos2d::ui;

Scene* SkyMapScene::createScene() {

	return SkyMapScene::create();

}

bool SkyMapScene::init() {

	if (!Scene::init())
		return false;

	skyMap = TMXTiledMap::create("MAP/SKY/TileMap1.tmx");
	
	this->addChild(skyMap, -1);
	if (skyMap == nullptr)
		return false;

	Object = skyMap->getObjectGroup("Object");

	InitUI();

	InitEvent();

	return true;

}

bool SkyMapScene::InitUI() {

	/*��Ӳ˵���ť*/
	ValueMap menu = Object->getObject("menuButton");
	float x = menu["x"].asFloat();
	float y = menu["y"].asFloat();

	menuButton = Button::create("MAP/menuButton_normal.png", "MAP/menuButton_pressed.png","");
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

void SkyMapScene::InitEvent() {

	/*��ʼ���˵���ť*/
	menuButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {

			auto choosemenu = ChooseMenu::createLayer();
			this->addChild(choosemenu);

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