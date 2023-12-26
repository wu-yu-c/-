#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include<vector>

typedef enum {
	None,Death,Bite
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

protected:

	CC_SYNTHESIZE(int, maxHp, Maxhp);                  //���Ѫ��
	CC_SYNTHESIZE(int, Hp, Hp);                      //��ǰѪ��
	int speed;                  //�ٶ�
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
	state State;

	void InitHpbar();

	void runNextPoint();

	void birthAnimation();

	void killAnimation();

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
