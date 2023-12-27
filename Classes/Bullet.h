#pragma once
#include "cocos2d.h"
#include"Monster.h"
USING_NS_CC;

class Bullet : public Sprite
{
public:

	CREATE_FUNC(Bullet);

protected:

	virtual bool init();

	int speed;

	CC_SYNTHESIZE(int, maxForce, MaxForce);//¹¥»÷Á¦
	CC_SYNTHESIZE(int, bulletScope, BulletScope);//ËþµÄ×Óµ¯¹¥»÷·¶Î§
	virtual void shoot() {};//¹¥»÷

};

class BottleBullet :public Bullet {
public:
	bool init();
	CREATE_FUNC(BottleBullet);
	void shoot();
};

class FlowerBullet :public Bullet {
public:
	virtual bool init();
	CREATE_FUNC(FlowerBullet);
	void shoot();
	void removeBullet();
};