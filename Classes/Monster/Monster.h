#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include<vector>

typedef enum {
	None,Death,Bite,Burn,Ice,Boom,IceBoom
} state;

typedef enum {
	normal, fly, big
} monsterName;

class Monster:public cocos2d::Sprite {
public:
	CREATE_FUNC(Monster);
	
	Monster* createMonster();

	Monster();

	virtual bool init() override;

	void loadPoint();

	void update(float dt) override;

	void getHurt(int hurt, state effect = None);

	CC_SYNTHESIZE(bool, chosen, Chosen);

	bool IsReverse;

protected:

	CC_SYNTHESIZE(float, maxHp, Maxhp);                  //���Ѫ��
	CC_SYNTHESIZE(float, Hp, Hp);                      //��ǰѪ��
	CC_SYNTHESIZE(int,speed,speed);                                         //�ٶ�
	int normalspeed;
	int slowspeed;                                     //���ٺ��ٶ�
	CC_SYNTHESIZE(int, money, Money);                  //�����
	float walklong;             //һ���ƶ��ľ���
	int width;
	int height;                 //�߶ȣ���������Ѫ���߶�
	size_t pointCounter;
	CC_SYNTHESIZE(cocos2d::ProgressTimer*, hpbar, Hpbar);     //Ѫ��
	cocos2d::Sprite* hpbar_bg;         //Ѫ������
	std::vector<cocos2d::Point> next;
	cocos2d::Vec2 nextPoint();
	cocos2d::Vec2 tmp;         //��һ������
	CC_SYNTHESIZE(cocos2d::Vec2,current,Current);      //��ǰ����
	bool isReverse;
	CC_SYNTHESIZE(state, State, nextState);

	CC_SYNTHESIZE(bool, IsEffect, Effect);

	void InitHpbar();

	void runNextPoint();

	void birthAnimation();

	void killAnimation();

	void attackAnimation();

	void reverseHpbar();

	void InitEvent();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

class NormalMonster :public Monster {
public:
	static NormalMonster* createMonster();

	virtual bool init();

	//void update(float dt);

	void InitAnimation();

	CREATE_FUNC(NormalMonster);
};

class FlyMonster :public Monster {
public:
	static FlyMonster* createMonster();

	virtual bool init();

	void InitAnimation();

	CREATE_FUNC(FlyMonster);
};

class BigMonster :public Monster {
public:
	static BigMonster* createMonster();

	virtual bool init();

	void InitAnimation();

	CREATE_FUNC(BigMonster);
};
