#include"Menu.h"
#include"MAP.h"
#include"GameManager.h"
USING_NS_CC;
using namespace cocos2d::ui;

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

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*��Ӳ˵�����*/
	Sprite* choosemenu = Sprite::create("MAP/Menu.png");
	choosemenu->setPosition(Vec2(origin.x + 568, origin.y + 320));
	this->addChild(choosemenu, 1);
	if (choosemenu == nullptr)
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
	/*�������¿�ʼ��ť*/
	restartButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			director->resume();
			Director::getInstance()->popScene();

		}
		});

	/*���÷��ذ�ť*/
	returnButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			director->resume();
			Director::getInstance()->popScene();

		}
		});

}

Layer* OverMenu::createMenu(bool IsWin, int max,int current) {

	OverMenu* menu = OverMenu::create();

	menu->Win = IsWin;

	menu->maxWave = max;

	menu->wave = current + 1;

	menu->InitMenu();

	return menu;

}

bool OverMenu::InitMenu() {

	if (!Layer::init())
		return false;

	char namesize[15] = { 0 };
	if (Win)
		sprintf(namesize, "MAP/win.png");
	else
		sprintf(namesize, "MAP/lose.png");

	auto bg = Sprite::create(namesize);

	addChild(bg, -1);

	InitUI();

	InitEvent();

	GameManager::getGame()->setResult();

	return true;

}

void OverMenu::InitUI() {

	Vec2 adjust;

	if (Win)         //�������
		adjust = Vec2(12, 10);
	else
		adjust = Vec2(0, 0);

	/*���ѡ��ؿ���ť*/
	returnButton = Button::create("MAP/returnButton_normal.png", "MAP/returnButton_pressed.png");
	returnButton->setScale(0.8f);
	returnButton->setPosition(Vec2(-100, -80) + adjust);
	addChild(returnButton);

	/*��Ӽ�����Ϸ��ť*/
	continueButton = Button::create("MAP/continueButton_normal.png", "MAP/continueButton_pressed.png");
	continueButton->setScale(0.8f);
	continueButton->setPosition(Vec2(70, -80) + adjust);
	addChild(continueButton);

	/*��ӹ����ܲ���*/
	auto number_1 = Sprite::create();
	number_1->setPosition(Vec2(40, 15) + adjust);
	addChild(number_1);
	MAP::setNumber(maxWave / 10, number_1);
	auto number_2 = Sprite::create();
	number_2->setPosition(Vec2(60, 15) + adjust);
	addChild(number_2);
	MAP::setNumber(maxWave % 10, number_2);

	/*��ӵ�ǰ���ﲨ��*/
	auto number_3 = Sprite::create();
	number_3->setPosition(Vec2(-30, 15) + adjust);
	addChild(number_3);
	MAP::setNumber(wave / 10, number_3, yellow);
	auto number_4 = Sprite::create();
	number_4->setPosition(Vec2(0, 15) + adjust);
	addChild(number_4);
	MAP::setNumber(wave % 10, number_4, yellow);

}

void OverMenu::InitEvent() {

	/*����ѡ��ؿ���ť*/
	returnButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {

			Director::getInstance()->resume();
			Director::getInstance()->popScene();

		}
		});

	/*���ü�����Ϸ��ť*/
	continueButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {

			Director::getInstance()->resume();
			Director::getInstance()->popScene();
			if (GameManager::getGame()->currentLevel < GameManager::getGame()->maxLevel)
				Director::getInstance()->pushScene(DesertMap::createGame());
		}
		});

}