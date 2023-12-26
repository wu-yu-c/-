#include"Monster.h"
#include"GameManager.h"
#include"MAP.h"
USING_NS_CC;
using namespace cocos2d::ui;

Monster::Monster() :
	speed(0),
	Hp(0),
	State(None),
	money(0) {

}

Monster* Monster::createMonster() {

	return Monster::create();
}

void Monster::loadPoint() {
	Vec2 birthPlace = static_cast<MAP*>(Director::getInstance()->getRunningScene())->getBirthPlace();
	const std::vector<Point>& corner = static_cast<MAP*>(Director::getInstance()->getRunningScene())->getCorner();
	const std::vector<Point>& path = static_cast<MAP*>(Director::getInstance()->getRunningScene())->getPath();
	walklong = path[0].getDistance(path[1]);
	for (size_t i = 0, j = 0; i < path.size(); i++) {
		if (abs(path[i].x - corner[j].x) < walklong && abs(path[i].y - corner[j].y) < walklong && j < corner.size()) {
			next.push_back(corner[j]);
			j++;
		}
		else
			next.push_back(path[i]);
	}
	current = birthPlace;
}

bool Monster::init() {
	if (!Sprite::init())
		return false;

	return true;
}

void Monster::InitHpbar() {

	hpbar_bg = Sprite::create("Monster/hpbar_bg.png");
	hpbar_bg->setPosition(Vec2(width,height));
	addChild(hpbar_bg);

	hpbar = ProgressTimer::create(Sprite::create("Monster/hpbar.png"));
	hpbar->setType(ProgressTimer::Type::BAR);
	hpbar->setMidpoint(Point(0, 0.5f));
	hpbar->setBarChangeRate(Point(1, 0));
	hpbar->setPercentage(100);
	hpbar->setPosition(Vec2(22.5f,5.8f));
	hpbar_bg->addChild(hpbar);

}

void Monster::birthAnimation() {

	auto animation = Animation::create();

	/*读取动画的帧*/
	animation->addSpriteFrameWithFile("MONSTER/birthaction1.png");
	animation->addSpriteFrameWithFile("MONSTER/birthaction2.png");

	/*动画设置为循环一次*/
	animation->setLoops(1);
	/*设置两帧间隔时间*/
	animation->setDelayPerUnit(0.1f);

	/*创建动画*/
	auto action = Animate::create(animation);
	/*对象运行该动画*/
	runAction(action);

}

void Monster::killAnimation() {
	stopAllActions();
	removeAllChildrenWithCleanup(true);
	GameManager::getGame()->Money += money;

	auto killed = Animation::create();

	char namesize[20] = { 0 };
	for (int i = 1; i <= 4; i++) {
		sprintf(namesize, "MONSTER/die_%d.png", i);
		killed->addSpriteFrameWithFile(namesize);
	}

	killed->setLoops(1);
	killed->setDelayPerUnit(0.1f);

	auto smoke = Animate::create(killed);

	runAction(Sequence::create(smoke,
		CallFuncN::create(CC_CALLBACK_0(MAP::addMoney,static_cast<MAP*>(Director::getInstance()->getRunningScene()), money, getPosition())),
		CallFuncN::create(CC_CALLBACK_0(Monster::removeFromParent, this)), NULL));

	GameManager::getGame()->currentMonster.eraseObject(this);

}

Vec2 Monster::nextPoint() {
	auto maxCount = next.size();
	pointCounter++;
	if (pointCounter < maxCount)
		return next[pointCounter];
	else
		pointCounter = maxCount - 1;
	return current;
}

void Monster::runNextPoint() {


	tmp = nextPoint();

	if (tmp != current) {
		auto duration = current.getDistance(tmp) / speed;
		
		if (abs(tmp.x - current.x) > walklong && pointCounter > 1) {
			//State = Death;
			runAction(Sequence::create(MoveTo::create(duration, tmp)
				,ScaleBy::create(0.1f, -1, 1)
				, CallFuncN::create(CC_CALLBACK_0(Monster::runNextPoint, this))
				, NULL));
		}
		else {
			runAction(Sequence::create(MoveTo::create(duration, tmp)
				, CallFuncN::create(CC_CALLBACK_0(Monster::runNextPoint, this))
				, NULL));
		}
		current = tmp;
	}
	else {
		State = Bite;
	}
}


NormalMonster* NormalMonster::createMonster()
{

	/*先创建一个实例*/
	auto normal = NormalMonster::create();

	return normal;

}

bool NormalMonster::init() {
	if (!Sprite::init())
		return false;

	maxHp=Hp = 35;

	money = 50;

	speed = 100;

	width = 27;
	height = 55;

	scheduleUpdate();

	loadPoint();

	InitAnimation();

	InitHpbar();

	runNextPoint();

	return true;
}

/*怪物的多种状态*/
void Monster::update(float dt) {

	switch (State) {
	case(Bite):
		GameManager::getGame()->Life--;
		unscheduleUpdate();
		removeFromParentAndCleanup(true);
		break;
	case(Death):
		killAnimation();
		unscheduleUpdate();
		break;
	default:
		break;
	}

}

/*初始化动画*/
void NormalMonster::InitAnimation() {

	auto animation = Animation::create();

	/*读取动画的帧*/
	char namesize[50] = { 0 };
	for (int i = 1; i <= 2; i++) {
		sprintf(namesize, "MONSTER/NormalMonster/action%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	/*动画设置为无限循环*/
	animation->setLoops(-1);
	/*设置两帧间隔时间*/
	animation->setDelayPerUnit(0.1f);

	/*创建动画*/
	auto action = Animate::create(animation);
	/*对象运行该动画*/
	runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_0(Monster::birthAnimation, this)), action,NULL));

}

FlyMonster* FlyMonster::createMonster()
{
	auto fly = FlyMonster::create();
	
	fly->InitAnimation();

	return fly;
}

bool FlyMonster::init() {
	if (!Sprite::init())
		return false;

	maxHp = Hp = 30;

	money = 75;

	speed = 200;

	width = 40;
	height = 65;

	scheduleUpdate();

	loadPoint();

	InitAnimation();

	InitHpbar();

	runNextPoint();

	return true;
}

void FlyMonster::InitAnimation() {

	auto animation = Animation::create();

	/*读取动画的帧*/
	char namesize[50] = { 0 };
	for (int i = 1; i <= 2; i++) {
		sprintf(namesize, "MONSTER/FlyMonster/action%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	/*动画设置为无限循环*/
	animation->setLoops(-1);
	/*设置两帧间隔时间*/
	animation->setDelayPerUnit(0.1f);

	/*创建动画*/
	auto action = Animate::create(animation);
	/*对象运行该动画*/
	runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_0(Monster::birthAnimation, this)), action,NULL));

}

BigMonster* BigMonster::createMonster()
{
	auto big = BigMonster::create();

	big->InitAnimation();

	return big;
}


bool BigMonster::init() {
	if (!Sprite::init())
		return false;

	maxHp = Hp = 50;

	money = 150;

	speed = 100;

	width = 40;
	height = 85;

	scheduleUpdate();

	loadPoint();

	InitAnimation();

	InitHpbar();

	runNextPoint();

	return true;
}

void BigMonster::InitAnimation() {

	auto animation = Animation::create();

	/*读取动画的帧*/
	char namesize[50] = { 0 };
	for (int i = 1; i <= 2; i++) {
		sprintf(namesize, "MONSTER/BigMonster/action%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	/*动画设置为无限循环*/
	animation->setLoops(-1);
	/*设置两帧间隔时间*/
	animation->setDelayPerUnit(0.1f);

	/*创建动画*/
	auto action = Animate::create(animation);
	/*对象运行该动画*/
	runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_0(Monster::birthAnimation, this)), action,NULL));
	
}

