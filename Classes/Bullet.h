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
	CC_SYNTHESIZE(int, maxForce, MaxForce);//������
	CC_SYNTHESIZE(int, bulletScope, BulletScope);//�����ӵ�������Χ
	CC_SYNTHESIZE(int, bulletType, BulletType);//�ӵ�����
	CC_SYNTHESIZE(Spawn*, bulletAction, BulletAction);//�ӵ����ж���
	Sprite* sprite;//�ӵ�����-��ͼ
	virtual void shoot() {};//����
	virtual void removeBullet() {};//������Ϻ��Ƴ�
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