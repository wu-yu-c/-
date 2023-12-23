#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

typedef enum {
	None,walkRigth, walkLeft, walkUp, walkDown
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

protected:

	int Hp;                     //血量
	int speed;                  //速度
	int money;                  //金币数
	cocos2d::Vec2 cuurenPoint();
	cocos2d::Vec2 nextPoint();
	cocos2d::Vec2 next;
	void runNextPoint();
	state currentState;
	state nextState;

	//virtual void update(float dt);

	cocos2d::Animate* action;   //动画

};

class NormalMonster :public Monster {
public:
	static Monster* createMonster();

	virtual bool init();

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
