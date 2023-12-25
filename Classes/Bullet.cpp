#include "Bullet.h"
#include "MAP.h"
bool BottleBullet::init()
{
	if (!Sprite::init())
		return false;
	sprite = Sprite::create("PBottle11.png");
	addChild(sprite);
	return true;
}

void BottleBullet::shoot()
{
	//BulletSound::BottleSound();//²¥·ÅÒôÐ§
	runAction(Sequence::create(bulletAction,
		CallFuncN::create(CC_CALLBACK_0(BottleBullet::removeBullet, this)),
		NULL));
}

void BottleBullet::removeBullet()
{
	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height / 2,
		this->sprite->getContentSize().width,
		this->sprite->getContentSize().height);

	auto nowMonster = static_cast<MAP*>(Director::getInstance()->getRunningScene())->currentMonster;

	for (int j = 0; j < nowMonster.size(); j++)
	{
		auto monster = nowMonster.at(j);
		auto monsterRect = monster->getBoundingBox();

		if (monsterRect.intersectsRect(bulletRect))
		{
			auto currHp = monster->getHp();

			currHp = currHp - this->getMaxForce();

			if (currHp <= 0) {
				currHp = 0;
			}
			monster->setHp(currHp);

			monster->getHpbar()->setPercentage((currHp / monster->getMaxhp()) * 100);

			/*if (currHp == 0) {
				monster->death();
			}*/
			break;
		}
	}
	this->removeFromParent();
}
