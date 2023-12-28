#include "Bullet.h"
#include "MAP.h"
#include"GameManager.h"


bool Bullet::init()
{
	if (!Sprite::init())
		return false;

	return true;
}

bool BottleBullet::init() {

	if (!Sprite::init())
		return false;

	return true;

}

void BottleBullet::shoot(int level) {

	auto animation = Animation::create();

	char namesize[30] = { 0 };
	for (int i = 1; i <= 3; i++) {
		sprintf(namesize, "Bottle/PBottle%d%d.png", level, i);
		animation->addSpriteFrameWithFile(namesize);
	}

	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	auto shoot = Animate::create(animation);
	runAction(shoot);

}

bool FlowerBullet::init() {

	if (!Sprite::create())
		return false;

	return true;

}

void FlowerBullet::shoot(int level) {

	auto animation = Animation::create();

	char namesize[30] = { 0 };
	for (int i = 1; i <= 3; i++) {
		sprintf(namesize, "Flower/PFlower%d%d.png", level, i);
		animation->addSpriteFrameWithFile(namesize);
	}

	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	auto shoot = Animate::create(animation);
	runAction(shoot);

}

//void StarBullet::shoot(int level) {
//
//
//	char namseize[30] = { 0 };
//	//setTexture("")
//
//}


