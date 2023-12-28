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

	virtual void shoot() {};//¹¥»÷

};

class BottleBullet :public Bullet {
public:
	bool init();
	CREATE_FUNC(BottleBullet);
	void shoot(int level);
};

class FlowerBullet :public Bullet {
public:
	virtual bool init();
	CREATE_FUNC(FlowerBullet);
	void shoot(int level);
};