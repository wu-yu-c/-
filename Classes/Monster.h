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

	Sprite* baseSprite;

	void loadPoint();

	void update(float dt) override;

protected:

	int maxHp;                   //最大血量
	int Hp;                      //当前血量
	int speed;                  //速度
	int money;                  //金币数
	float walklong;             //
	int width;
	int height;                 //高度，方便设置血条高度
	int pointCounter;
	cocos2d::ProgressTimer* hpbar;     //血条
	cocos2d::Sprite* hpbar_bg;         //血条背景
	std::vector<cocos2d::Point> next;
	cocos2d::Vec2 nextPoint();
	cocos2d::Vec2 tmp;         //下一步坐标
	CC_SYNTHESIZE(cocos2d::Vec2,current,Current);      //当前坐标
	bool isReverse;
	state State;

	void InitHpbar();

	void runNextPoint();

};

class NormalMonster :public Monster {
public:
	static Monster* createMonster();

	virtual bool init();

	//void update(float dt);

	void InitAnimation();

	CREATE_FUNC(NormalMonster);
};

class FlyMonster :public Monster {
public:
	static Monster* createMonster();

	virtual bool init();

	void InitAnimation();

	CREATE_FUNC(FlyMonster);
};

class BigMonster :public Monster {
public:
	static Monster* createMonster();

	virtual bool init();

	void InitAnimation();

	CREATE_FUNC(BigMonster);
};
