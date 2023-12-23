#include"MAP.h"
#include"Monster.h"
USING_NS_CC;
using namespace cocos2d::ui;

void SkyMapScene::loadPath() {

	float x, y;

	Corner = tilemap->getObjectGroup("Corner");

	/*创建几段移动动作，corner坐标从瓦片地图获取*/
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

	/*镜面翻转动作*/
	auto reverse = ScaleBy::create(0.1f, -1, 1);

	/*创建动作序列*/
	movepath = Sequence::create(move1, reverse, move2, move3, reverse, move4, move5, NULL);

}

void DesertMapScene::loadPath() {

	float x, y;

	Corner = tilemap->getObjectGroup("Corner");

	/*创建几段移动动作，corner坐标从瓦片地图获取*/
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

	/*创建动作序列*/
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
	const int numOfMonsters = 5; // 每次生成5个怪物
	for (int i = 0; i < numOfMonsters; ++i) {
		auto monster = NormalMonster::createMonster();
		monster->setPosition(birthPlace->getPosition()); // 设置怪物的初始位置
		monster->runAction(movepath);
		this->addChild(monster); // 添加到场景中
		
	}
}
/*初始化怪物*/
void MAP::InitMonster() {
	/*创建普通怪物*/
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

	/*添加菜单按钮*/
	ValueMap menu = Object->getObject("menuButton");               //通过对象名字读取一个object
	float x = menu["x"].asFloat();                                 //获取该对象在地图上的x坐标
	float y = menu["y"].asFloat();                                 //获取该对象在地图上的y坐标

	menuButton = Button::create("MAP/menuButton_normal.png", "MAP/menuButton_pressed.png","");             //创建按钮
	menuButton->setPosition(Vec2(x, y));                           //放到对象位置
	menuButton->setPressedActionEnabled(true);
	addChild(menuButton, 1);
	if (menuButton == nullptr)
		return false;


	/*添加暂停按钮*/
	ValueMap stop = Object->getObject("stopButton");
	x = stop["x"].asFloat();
	y = stop["y"].asFloat();

	stopButton = Button::create("MAP/stopButton_normal.png", "MAP/stopButton_pressed.png", "");
	stopButton->setPosition(Vec2(x, y));
	stopButton->setPressedActionEnabled(true);
	addChild(stopButton, 1);
	if (stopButton == nullptr)
		return false;

	/*添加继续游戏按钮*/
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	continueButton = Button::create("MAP/continueBUtton_normal.png", "MAP/continueButton_pressed.png");
	continueButton->setPosition(Vec2(origin.x + 565, origin.y + 395));
	continueButton->setVisible(false);//初始设置为不可见
	this->addChild(continueButton, 2);
	if (continueButton == nullptr)
		return false;

	/*添加怪物出生点*/
	ValueMap birth = Object->getObject("birth");
	x = birth["x"].asFloat();
	y = birth["y"].asFloat();

	birthPlace = Sprite::create("MAP/SKY/birth.png");
	birthPlace->setPosition(x, y);
	addChild(birthPlace);
	if (birthPlace == nullptr)
		return false;

	/*添加萝卜*/
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
	static int count = 0;//检测按下暂停按钮时的状态
	/*初始化菜单按钮*/
	menuButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			chooseMenu = ChooseMenu::createLayer();
			Director::getInstance()->pause();
			addChild(chooseMenu);
			continueButton->setVisible(true);
		}
		});

	/*设置继续游戏按钮*/
	continueButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			director->resume();
			chooseMenu->removeFromParent();
			continueButton->setVisible(false);//重新设置为不可见
		}
		});

	//设置暂停按钮
	stopButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			//若为偶数次按下，则暂停动画
			if (count % 2 == 0)
				director->stopAnimation();
			//否则，使动画重新开始
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
	/*添加菜单背景*/
	Sprite* choosemenu = Sprite::create("MAP/Menu.png");
	choosemenu->setPosition(Vec2(origin.x + 568, origin.y + 320));
	this->addChild(choosemenu, 1);
	if (choosemenu == nullptr)
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
	/*设置重新开始按钮*/
	restartButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			director->resume();
			Director::getInstance()->popScene();

		}
		});

	/*设置返回按钮*/
	returnButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto director = Director::getInstance();
			director->resume();
			Director::getInstance()->popScene();

		}
		});

}