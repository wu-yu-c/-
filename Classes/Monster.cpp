#include"Monster.h"
USING_NS_CC;
using namespace cocos2d::ui;

Monster* NormalMonster::createMonster() {

	/*先创建一个实例*/
	auto normal = NormalMonster::create();
	
	normal->InitAnimation();

	return normal;

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
	action = Animate::create(animation);
	/*对象运行该动画*/
	runAction(action);

}