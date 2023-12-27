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

void BottleBullet::shoot() {

	Sprite* bullet = Sprite::create();
	
	auto animation = Animation::create();
	animation->addSpriteFrameWithFile("Bottle/PBottle11.png");
	animation->addSpriteFrameWithFile("Bottle/PBottle12.png");
	animation->addSpriteFrameWithFile("Bottle/PBottle13.png");

	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	auto shoot = Animate::create(animation);
	runAction(shoot);

}


