#include"Monster.h"
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

bool Monster::init() {
	if (!Sprite::init())
		return false;

	return true;
}


Monster* NormalMonster::createMonster()
{

	/*�ȴ���һ��ʵ��*/
	auto normal = NormalMonster::create();

	//normal->setPosition(begin);

	//normal->InitAnimation();

	return normal;

}

bool NormalMonster::init() {
	if (!Sprite::init())
		return false;

	InitAnimation();

	return true;
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
	action = Animate::create(animation);
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

	InitAnimation();

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
	action = Animate::create(animation);
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

	InitAnimation();

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
	action = Animate::create(animation);
	/*�������иö���*/
	runAction(action);

}

