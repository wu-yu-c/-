#include"MAP.h"
#include"Monster.h"
USING_NS_CC;
using namespace cocos2d::ui;

/*��ʼ������*/
void MAP::addWaves(float dt) {

	if (wave < maxWave - 1 && currentMonster.size() == 0) {

		IsStart = true;
		wave++;
		schedule(schedule_selector(MAP::addMonsters), 1.0f, waveMonster.at(wave).size(), 0);
	}

}

void MAP::addMonsters(float dt) {
	if (MonsterNum < waveMonster.at(wave).size()) {
		Monster* monster = NULL;
		switch (waveMonster.at(wave).at(MonsterNum)) {
		case(normal):
			monster = NormalMonster::createMonster();
			break;
		case(fly):
			monster = FlyMonster::createMonster();
			break;
		case(big):
			monster = BigMonster::createMonster();
			break;
		default:
			break;
		}
		monster->setPosition(begin);
		monster->setCurrent(begin);
		addChild(monster);
		currentMonster.pushBack(monster);
		MonsterNum++;
	}
	else {
		MonsterNum = 0;
		if (wave == maxWave - 1)
			IsEnd = true;
	}
}

void MAP::updateMoneyandLife() {

}

void MAP::update(float dt){

	updateMoneyandLife();

}

void MAP::InitMap() {
	scheduleUpdate();

	MonsterNum = 0;

	wave = -1;

	maxLife = life = 10;

	IsStart = IsEnd = false;

	InitUI();

	InitEvent();

	beginAnimation();

}

void MAP::beginAnimation() {
	schedule(schedule_selector(MAP::addWaves), 1.0f);
}

bool MAP::InitUI() {

	/*��Ӳ˵���ť*/
	ValueMap menu = Object->getObject("menuButton");               //ͨ���������ֶ�ȡһ��object
	float x = menu["x"].asFloat();                                 //��ȡ�ö����ڵ�ͼ�ϵ�x����
	float y = menu["y"].asFloat();                                 //��ȡ�ö����ڵ�ͼ�ϵ�y����

	menuButton = Button::create("MAP/menuButton_normal.png", "MAP/menuButton_pressed.png","");             //������ť
	menuButton->setPosition(Vec2(x, y));                           //�ŵ�����λ��
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

	/*��Ӽ�����Ϸ��ť*/
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	continueButton = Button::create("MAP/continueBUtton_normal.png", "MAP/continueButton_pressed.png");
	continueButton->setPosition(Vec2(origin.x + 565, origin.y + 395));
	continueButton->setVisible(false);//��ʼ����Ϊ���ɼ�
	this->addChild(continueButton, 2);
	if (continueButton == nullptr)
		return false;

	/*��ӹ��������*/
	ValueMap birth = Object->getObject("birth");
	x = birth["x"].asFloat();
	y = birth["y"].asFloat();
	begin = Vec2(x, y);

	birthPlace = Sprite::create("MAP/SKY/birth.png");
	birthPlace->setPosition(x, y);
	addChild(birthPlace);
	if (birthPlace == nullptr)
		return false;

	/*����ܲ�*/
	ValueMap carrotloc = Object->getObject("carrot");
	x = carrotloc["x"].asFloat();
	y = carrotloc["y"].asFloat();

	Carrot = Sprite::create("Carrot/carrot_10.png");
	Carrot->setPosition(x, y + 25);
	Carrot->setScale(0.6f);
	addChild(Carrot);
	if (Carrot == nullptr)
		return false;

	return true;
}

void MAP::InitEvent() {
	static int count = 0;//��ⰴ����ͣ��ťʱ��״̬
	/*��ʼ���˵���ť*/
	menuButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			chooseMenu = ChooseMenu::createLayer();
			Director::getInstance()->pause();
			addChild(chooseMenu);
			continueButton->setVisible(true);
		}
		});

	/*���ü�����Ϸ��ť*/
	continueButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			director->resume();
			chooseMenu->removeFromParent();
			continueButton->setVisible(false);//��������Ϊ���ɼ�
		}
		});

	//������ͣ��ť
	stopButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			//��Ϊż���ΰ��£�����ͣ����
			if (count % 2 == 0)
				director->stopAnimation();
			//����ʹ�������¿�ʼ
			else
				director->startAnimation();
			count++;
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