#include"Carrot.h"
#include"MAP.h"
USING_NS_CC;
using namespace cocos2d::ui;

bool Carrot::init() {

	if (!Sprite::init())
		return false;

	Life = 10;

	life = Sprite::create("Carrot/life_10.png");
	this->addChild(life);
	life->setPosition(Vec2(150,100));

	InitAnimation();

	return true;
}

void Carrot::setLife(int n) {

	stopAllActions();
	char namesize[20] = { 0 };

	sprintf(namesize, "Carrot/life_%d.png", n);
	life->setTexture(namesize);

	sprintf(namesize, "Carrot/hlb1_%d.png", n);
	setTexture(namesize);


}

void Carrot::InitAnimation() {

	auto animation = Animation::create();

	char namesize[25] = { 0 };
	for (int i = 10; i <= 21; i++) {
		sprintf(namesize, "Carrot/hlb1_%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	animation->addSpriteFrameWithFile("Carrot/hlb1_10.png");
	animation->setLoops(1);
	/*设置两帧间隔时间*/
	animation->setDelayPerUnit(0.1f);

	/*创建动画*/
	shake = Animate::create(animation);
	/*对象运行该动画*/

	runAction(shake);
	//schedule(schedule_selector(Carrot::Move), 5.0f);
}

void Carrot::Move(float dt) {
	if (Life >= 10) {
		stopAction(shake);
		runAction(shake);
	}
	else
		unschedule(schedule_selector(Carrot::Move));
}