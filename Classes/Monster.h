#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include<vector>

typedef enum {
	None,Death,Slow
} state;

typedef enum {
	normal, fly, big
} monsterName;

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

<<<<<<< Updated upstream
=======
	void loadPoint();

>>>>>>> Stashed changes
protected:

	int Hp;                     //血量
	int speed;                  //速度
	int money;                  //金币数
<<<<<<< Updated upstream
	cocos2d::Vec2 cuurenPoint();
	cocos2d::Vec2 nextPoint();
	cocos2d::Vec2 next;
	void runNextPoint();
	state currentState;
	state nextState;

	//virtual void update(float dt);

	cocos2d::Animate* action;   //动画
=======
	int pointCounter;        
	std::vector<cocos2d::Point> next;
	std::vector<cocos2d::Point> turn;
	cocos2d::Vec2 nextPoint();
	cocos2d::Vec2 tmp;         //下一步坐标
	CC_SYNTHESIZE(cocos2d::Vec2,current,Current);      //当前坐标
	bool isReverse;
	state currentState;
	state nextState;

	void runNextPoint();
>>>>>>> Stashed changes

};

class NormalMonster :public Monster {
public:
	static Monster* createMonster();

	virtual bool init();

<<<<<<< Updated upstream
=======
	void update(float dt);

>>>>>>> Stashed changes
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
