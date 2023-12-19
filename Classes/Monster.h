#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Monster:public cocos2d::Sprite {
public:
	int Hp;                     //血量
	int speed;                  //速度
	cocos2d::Vec2  loc;         //当前位置
	CREATE_FUNC(Monster);

	cocos2d::Animate* action;   //移动动画

};

class NormalMonster :public Monster {
public:
	static Monster* createMonster();

	void InitAnimation();

	CREATE_FUNC(NormalMonster);
};

class FlyMonster :public Monster {
public:
	static Monster* createMonster();

	void InitAnimation();

	CREATE_FUNC(FlyMonster);
};

class BigMonster :public Monster {
public:
	static Monster* createMonster();

	void InitAnimation();

	CREATE_FUNC(BigMonster);
};