#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Bullet : public Sprite
{
public:
	Bullet() :sprite(NULL), maxForce(0), bulletScope(0) {};
	~Bullet() {};
	virtual bool init() {
		if (!Sprite::init())
		{
			return false;
		}
		return true;
	};
	CREATE_FUNC(Bullet);

protected:
	CC_SYNTHESIZE(int, maxForce, MaxForce);//攻击力
	CC_SYNTHESIZE(int, bulletScope, BulletScope);//塔的子弹攻击范围
	CC_SYNTHESIZE(int, bulletType, BulletType);//子弹类型
	CC_SYNTHESIZE(Spawn*, bulletAction, BulletAction);//子弹飞行动画
	Sprite* sprite;//子弹精灵-贴图
	virtual void shoot() {};//攻击
	virtual void removeBullet() {};//攻击完毕后移除
};

class BottleBullet :public Bullet {
public:
	virtual bool init();
	CREATE_FUNC(BottleBullet);
	void shoot();
	void removeBullet();
};

class FlowerBullet :public Bullet {
public:
	virtual bool init();
	CREATE_FUNC(FlowerBullet);
	void shoot();
	void removeBullet();
};