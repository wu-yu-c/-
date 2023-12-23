#include"MAP.h"
#include"Monster.h"
USING_NS_CC;
using namespace cocos2d::ui;

void SkyMapScene::loadPath() {

	float x, y;

	Corner = tilemap->getObjectGroup("Corner");

	/*���������ƶ�������corner�������Ƭ��ͼ��ȡ*/
	const Vec2 begin = birthPlace->getPosition();
	
	ValueMap corner1 = Corner->getObject("corner1");
	x = corner1["x"].asFloat();
	y = corner1["y"].asFloat();
	auto move1 = MoveTo::create(3, Vec2(x, y));

	ValueMap corner2 = Corner->getObject("corner2");
	x = corner2["x"].asFloat();
	y = corner2["y"].asFloat();
	auto move2 = MoveTo::create(1, Vec2(x, y));

	ValueMap corner3 = Corner->getObject("corner3");
	x = corner3["x"].asFloat();
	y = corner3["y"].asFloat();
	auto move3 = MoveTo::create(4, Vec2(x, y));

	ValueMap corner4 = Corner->getObject("corner4");
	x = corner4["x"].asFloat();
	y = corner4["y"].asFloat();
	auto move4 = MoveTo::create(1, Vec2(x, y));

	const Vec2 end = Carrot->getPosition();
	auto move5 = MoveTo::create(3, end);

	/*���淭ת����*/
	auto reverse = ScaleBy::create(0.1f, -1, 1);

	/*������������*/
	movepath = Sequence::create(move1, reverse, move2, move3, reverse, move4, move5, NULL);

}

void DesertMapScene::loadPath() {

	float x, y;

	Corner = tilemap->getObjectGroup("Corner");

	/*���������ƶ�������corner�������Ƭ��ͼ��ȡ*/
	const Vec2 begin = birthPlace->getPosition();

	ValueMap corner1 = Corner->getObject("corner1");
	x = corner1["x"].asFloat();
	y = corner1["y"].asFloat();
	auto move1 = MoveTo::create(3, Vec2(x, y));

	ValueMap corner2 = Corner->getObject("corner2");
	x = corner2["x"].asFloat();
	y = corner2["y"].asFloat();
	auto move2 = MoveTo::create(3, Vec2(x, y));

	const Vec2 end = Carrot->getPosition();
	auto move3 = MoveTo::create(3, end);

	/*������������*/
	movepath = Sequence::create(move1, move2, move3, NULL);

}

SkyMapScene* SkyMapScene::createMap() {

	auto skymap = SkyMapScene::create();

	skymap->tilemap = TMXTiledMap::create("MAP/SKY/TileMap1.tmx");

	skymap->addChild(skymap->tilemap, -1);
	if (skymap->tilemap == nullptr)
		return false;

	skymap->Object = skymap->tilemap->getObjectGroup("Object");

	skymap->InitUI();

	skymap->InitEvent();

	skymap->loadPath();

	//skymap->roundMonster();
	//skymap->generateMonster(1.0);

	skymap->InitMonster();



	return skymap;

}

void MAP::roundMonster()
{
	schedule(schedule_selector(MAP::generateMonster), 2.0f);
}

void MAP::generateMonster(float dt) {
	const int numOfMonsters = 5; // ÿ������5������
	for (int i = 0; i < numOfMonsters; ++i) {
		auto monster = NormalMonster::createMonster();
		monster->setPosition(birthPlace->getPosition()); // ���ù���ĳ�ʼλ��
		monster->runAction(movepath);
		this->addChild(monster); // ��ӵ�������
		
	}
}
/*��ʼ������*/
void MAP::InitMonster() {
	/*������ͨ����*/
	Sprite* normal = NormalMonster::createMonster();

	normal->setPosition(birthPlace->getPosition());

	normal->runAction(movepath);

	this->addChild(normal);
}

DesertMapScene* DesertMapScene::createMap() {

	auto desertmap = DesertMapScene::create();

	desertmap->tilemap = TMXTiledMap::create("MAP/DESERT/TileMap2.tmx");

	desertmap->addChild(desertmap->tilemap, -1);
	if (desertmap->tilemap == nullptr)
		return false;

	desertmap->Object = desertmap->tilemap->getObjectGroup("Object");

	desertmap->InitUI();

	desertmap->InitEvent();

	desertmap->loadPath();

	desertmap->InitMonster();

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

	birthPlace = Sprite::create("MAP/SKY/birth.png");
	birthPlace->setPosition(x, y);
	addChild(birthPlace);
	if (birthPlace == nullptr)
		return false;

	/*����ܲ�*/
	ValueMap carrotloc = Object->getObject("carrot");
	x = carrotloc["x"].asFloat();
	y = carrotloc["y"].asFloat();

	Carrot = Sprite::create("Carrot/carrot_10(1).png");
	Carrot->setAnchorPoint(Vec2(0.5, 0.3f));
	Carrot->setPosition(x, y);
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
	//Ŀǰȫ������Ϊ����
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