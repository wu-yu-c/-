#pragma once
#include "cocos2d.h"
#include"Monster/Monster.h"
USING_NS_CC;

/*�ӵ��Ļ���*/
class Bullet : public Sprite
{
public:

	CREATE_FUNC(Bullet);

protected:

	virtual bool init();

	int speed;              //�ӵ������ٶ�

	virtual void shoot() {};//�ӵ���������

};

/*ƿ���ڵ��ӵ���*/
class BottleBullet :public Bullet {
public:
	bool init();
	CREATE_FUNC(BottleBullet);
	void shoot(int level);
};

/*�����ǵ��ӵ���*/
class StarBullet :public Bullet {
public:
	bool init();
	CREATE_FUNC(StarBullet);
	void shoot(int level);

};