#include"Carrot.h"
#include"MAP.h"
USING_NS_CC;
using namespace cocos2d::ui;

bool Carrot::init() {

	if (!Sprite::init())
		return false;

	Life = 10;

	this->setTexture("Carrot/hlb1_10.png");
	life = Sprite::create("Carrot/life_10.png");
	this->addChild(life);
	life->setPosition(Vec2(80,-20));

	schedule(schedule_selector(Carrot::shakeAnimation), 5.0f);

	return true;
}

void Carrot::setLife(int n) {

	Life = n;
	stopAllActions();
	char namesize[20] = { 0 };

	sprintf(namesize, "Carrot/life_%d.png", n);
	life->setTexture(namesize);

	sprintf(namesize, "Carrot/hlb1_%d.png", n);
	setTexture(namesize);


}

void Carrot::BiteCarrot(int n) {

	char namesize[20] = { 0 };
	auto animation = Animation::create();
	for (int i = 1; i <= 4; i++) {
		sprintf(namesize, "MAP/smoke_%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	auto bite = Animate::create(animation);
	runAction(Sequence::create(bite, CallFuncN::create(CC_CALLBACK_0(Carrot::setLife, this, n)), NULL));

}

void Carrot::shakeAnimation(float dt){

	if (Life >= 10) {
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
		auto shake = Animate::create(animation);
		/*对象运行该动画*/

		runAction(shake->clone());
		
	}
	else
		unschedule(schedule_selector(Carrot::shakeAnimation));

}
