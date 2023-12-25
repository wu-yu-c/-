#include"MAP.h"
#include"Monster.h"
USING_NS_CC;
using namespace cocos2d::ui;

/*初始化怪物*/
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

	currentLife = 10;

	wave = -1;

	IsStart = IsEnd = false;

	InitUI();

	InitEvent();

	beginAnimation();

}

void MAP::Count(int i) {

	auto fadein = FadeIn::create(0);
	auto fadeout = FadeOut::create(0);
	auto growBig = ScaleBy::create(0.5f, 1.5);
	auto growSmall = growBig->reverse();
	auto oneCount = Sequence::create(fadein, growBig, growSmall, fadeout, NULL);

	if (i >= 0) {

		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		Vec2 middle = Vec2(origin.x + 568, origin.y + 320);

		char namesize[50] = { 0 };
		sprintf(namesize, "MAP/Begin/count%d.png", i);
		auto number = Sprite::create(namesize);
		number->setPosition(middle);
		addChild(number);
		number->setTag(i);
		number->runAction(Sequence::create(oneCount, CallFuncN::create(CC_CALLBACK_0(MAP::Count, this,--i)), NULL));
	}
	else {
		unscheduleAllCallbacks();
		schedule(schedule_selector(MAP::addWaves), 1.0f);
	}

}

void MAP::beginAnimation() {

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 middle = Vec2(origin.x + 568, origin.y + 320);

	auto BG = Sprite::create("MAP/Begin/BG.png");
	BG->setPosition(middle);
	//addChild(BG);

	auto loop = Sprite::create("MAP/Begin/loop.png");
	auto rotate = RotateBy::create(1.0f, 360.0f);
	loop->setPosition(Vec2(0, 20));
	loop->setAnchorPoint(middle);
	//addChild(loop);

	Count(3);

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

	/*添加怪物波数*/
	ValueMap text = Object->getObject("text");
	x = text["x"].asFloat();
	y = text["y"].asFloat();
	auto TEXT = Sprite::create("MAP/TEXT.png");
	TEXT->setPosition(Vec2(x, y));
	addChild(TEXT);

	/*添加怪物出生点*/
	ValueMap birth = Object->getObject("birth");
	x = birth["x"].asFloat();
	y = birth["y"].asFloat();
	begin = Vec2(x, y);

	birthPlace = Sprite::create("MAP/SKY/birth.png");
	birthPlace->setPosition(x, y);
	addChild(birthPlace);
	if (birthPlace == nullptr)
		return false;

	/*添加萝卜*/
	ValueMap carrotloc = Object->getObject("carrot");
	x = carrotloc["x"].asFloat();
	y = carrotloc["y"].asFloat();

	carrot = Carrot::create();
	carrot->setPosition(x, y + 40);
	carrot->setScale(0.75f);
	addChild(carrot);
	if (carrot == nullptr)
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
			if (count % 2 == 0) {
				stopButton->loadTextures("MAP/pause.png", "MAP/pause.png", "");
				director->stopAnimation();
			}
			//否则，使动画重新开始
			else {
				stopButton->loadTextures("MAP/stopButton_normal.png", "MAP/stopButton_pressed.png", "");
				director->startAnimation();
			}
			count++;
		}
		});
}

void MAP::BiteCarrot() {
	
	char namesize[20] = { 0 };
	auto animation = Animation::create();
	for (int i = 1; i <= 4; i++) {
		sprintf(namesize, "MAP/smoke_%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	auto bite = Animate::create(animation);
	carrot->runAction(Sequence::create(bite, CallFuncN::create(CC_CALLBACK_0(Carrot::setLife, carrot, --currentLife)), NULL));

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