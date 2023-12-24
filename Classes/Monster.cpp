#include"Monster.h"
#include"MAP.h"
USING_NS_CC;
using namespace cocos2d::ui;

Monster::Monster() :
	baseSprite(NULL),
	speed(0),
	Hp(0),
	nextState(None),
	currentState(None),
	money(0) {

}

Monster* Monster::createMonster() {
	return Monster::create();
}

void Monster::loadPoint() {
	const std::vector<Point>& corner = static_cast<MAP*>(Director::getInstance()->getRunningScene())->getCorner();
	const std::vector<Point>& path = static_cast<MAP*>(Director::getInstance()->getRunningScene())->getPath();
	float width = path[0].getDistance(path[1]);
	for (int i = 0, j = 0; i < path.size(); i++) {
		next.push_back(path[i]);
	}
}

bool Monster::init() {
	if (!Sprite::init())
		return false;

	return true;
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
	/*auto reverse = ScaleBy::create(1, 1);
	for (int i = 0; i < turn.size(); i++) {
		if (tmp == turn[i]) {
			reverse = ScaleBy::create(-1, 1);
			break;
		}
	}*/

	if (tmp != current) {
		auto duration = current.getDistance(tmp) / speed;
		runAction(Sequence::create(MoveTo::create(duration, tmp)
			, CallFuncN::create(CC_CALLBACK_0(Monster::runNextPoint, this))
			/*, reverse*/
			, NULL));
		current = tmp;
	}
	else {
		unscheduleAllCallbacks();
	}
}


Monster* NormalMonster::createMonster()
{

	/*�ȴ���һ��ʵ��*/
	auto normal = NormalMonster::create();

	return normal;

}

bool NormalMonster::init() {
	if (!Sprite::init())
		return false;

	Hp = 35;

	money = 10;

	speed = 40;

	scheduleUpdate();

	loadPoint();

	InitAnimation();

	runNextPoint();

	return true;
}

void NormalMonster::update(float dt) {
	if (currentState != nextState) {
		switch (nextState) {
		case(Death):
			
			break;
		case(Slow):
			
			
			break;
		default:
			break;
		}
		currentState = nextState;
	}
}

/*��ʼ������*/
void NormalMonster::InitAnimation() {

	auto animation = Animation::create();

	/*��ȡ������֡*/
	char namesize[50] = { 0 };
	for (int i = 1; i <= 2; i++) {
		sprintf(namesize, "MONSTER/NormalMonster/action%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	/*��������Ϊ����ѭ��*/
	animation->setLoops(-1);
	/*������֡���ʱ��*/
	animation->setDelayPerUnit(0.1f);

	/*��������*/
	auto action = Animate::create(animation);
	/*�������иö���*/
	runAction(action);

}

Monster* FlyMonster::createMonster()
{
	auto fly = FlyMonster::create();
	
	fly->InitAnimation();

	return fly;
}

bool FlyMonster::init() {
	if (!Sprite::init())
		return false;

	Hp = 30;

	money = 15;

	speed = 60;

	scheduleUpdate();

	loadPoint();

	InitAnimation();

	runNextPoint();

	return true;
}

void FlyMonster::InitAnimation() {

	auto animation = Animation::create();

	/*��ȡ������֡*/
	char namesize[50] = { 0 };
	for (int i = 1; i <= 2; i++) {
		sprintf(namesize, "MONSTER/FlyMonster/action%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	/*��������Ϊ����ѭ��*/
	animation->setLoops(-1);
	/*������֡���ʱ��*/
	animation->setDelayPerUnit(0.1f);

	/*��������*/
	auto action = Animate::create(animation);
	/*�������иö���*/
	runAction(action);

}

Monster* BigMonster::createMonster()
{
	auto big = BigMonster::create();

	big->InitAnimation();

	return big;
}


bool BigMonster::init() {
	if (!Sprite::init())
		return false;

	Hp = 50;

	money = 20;

	speed = 100;

	scheduleUpdate();

	loadPoint();

	InitAnimation();

	runNextPoint();

	return true;
}

void BigMonster::InitAnimation() {

	auto animation = Animation::create();

	/*��ȡ������֡*/
	char namesize[50] = { 0 };
	for (int i = 1; i <= 2; i++) {
		sprintf(namesize, "MONSTER/BigMonster/action%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	/*��������Ϊ����ѭ��*/
	animation->setLoops(-1);
	/*������֡���ʱ��*/
	animation->setDelayPerUnit(0.1f);

	/*��������*/
	auto action = Animate::create(animation);
	/*�������иö���*/
	runAction(action);

}

