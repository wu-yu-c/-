#include"Menu/Menu.h"
#include"MAP/MAP.h"
#include"Manager/GameManager.h"
#include "Manager/SoundManager.h"
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
			SoundManager::StopBackgroundMusic();
			SoundManager::PlayMapMusic();
			Director::getInstance()->popScene();
			if (GameManager::getGame()->currentLevel == 1)
				Director::getInstance()->pushScene(SkyMap::createGame());
			else
				Director::getInstance()->pushScene(DesertMap::createGame());

		}
		});

	/*���÷��ذ�ť*/
	returnButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			director->resume();
			SoundManager::StopBackgroundMusic();
			SoundManager::PlayBackgroundMusic();
			Director::getInstance()->popScene();

		}
		});

}

Layer* OverMenu::createMenu(bool IsWin, int max,int current) {

	OverMenu* menu = OverMenu::create();

	menu->Win = IsWin;                     //������Ϸ���

	menu->maxWave = max;

	if (IsWin)
		menu->wave = current + 1;          //ʤ����ǰ������һ
	else
		menu->wave = current;

	menu->InitMenu();

	return menu;

}

/*��ʼ������˵�*/
bool OverMenu::InitMenu() {

	if (!Layer::init())
		return false;

	char namesize[15] = { 0 };
	if (Win)                                      //������Ϸ������ò�ͬ�Ľ���˵�
		sprintf(namesize, "MAP/win.png");          
	else
		sprintf(namesize, "MAP/lose.png");

	auto bg = Sprite::create(namesize);

	addChild(bg, -1);
	bg->setName("bg");

	InitUI();

	InitEvent();

	GameManager::getGame()->setResult();                     //������Ϸ���

	return true;

}

/*������Ϸ���*/
void OverMenu::Result() {

	auto bg = getChildByName("bg");

	Size size =bg->getContentSize();

	int life = GameManager::getGame()->Life;


	auto result = Sprite::create();

	result->setPosition(size.width / 2 - 5, size.height);

	bg->addChild(result);

	if (life >= 10)                                 //�����ܲ�ʣ������ֵ��ʾ��ͬ�Ľ��
		result->setTexture("MAP/carrot3.png");
	else if (life >= 4)
		result->setTexture("MAP/carrot2.png");
	else
		result->setTexture("MAP/carrot1.png");

}

void OverMenu::InitUI() {

	Vec2 adjust;

	if (Win) {         //�������
		adjust = Vec2(12, 10);
		Result();
	}
	else
		adjust = Vec2(0, 0);

	/*���ѡ��ؿ���ť*/
	returnButton = Button::create("MAP/returnButton_normal.png", "MAP/returnButton_pressed.png");
	returnButton->setScale(0.8f);
	returnButton->setPosition(Vec2(-100, -80) + adjust);
	addChild(returnButton);

	/*��Ӽ�����Ϸ��ť�����¿�ʼ��ť*/
	if (Win)
		continueButton = Button::create("MAP/continueButton_normal.png", "MAP/continueButton_pressed.png");
	else
		continueButton = Button::create("MAP/restartButton_normal.png", "MAP/restartButton_pressed.png");
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
			SoundManager::StopBackgroundMusic();
			SoundManager::PlayBackgroundMusic();
			Director::getInstance()->popScene();

		}
		});

	/*���ü�����Ϸ��ť*/
	continueButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			Director::getInstance()->popScene();
			if (GameManager::getGame()->currentLevel < GameManager::getGame()->maxLevel) {
				if (GameManager::getGame()->getResult(1))
					Director::getInstance()->pushScene(DesertMap::createGame());
				else
					Director::getInstance()->pushScene(SkyMap::createGame());
			}
			else
				SoundManager::PlayBackgroundMusic();
		}
		});

}