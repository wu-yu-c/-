#include"Monster.h"
USING_NS_CC;
using namespace cocos2d::ui;

Monster* NormalMonster::createMonster() {

	/*�ȴ���һ��ʵ��*/
	auto normal = NormalMonster::create();
	
	normal->InitAnimation();

	return normal;

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