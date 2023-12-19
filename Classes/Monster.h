#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Monster:public cocos2d::Sprite {
public:
	int Hp;                     //Ѫ��
	int speed;                  //�ٶ�
	cocos2d::Vec2  loc;         //��ǰλ��
	CREATE_FUNC(Monster);

	cocos2d::Animate* action;   //�ƶ�����

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