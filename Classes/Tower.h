#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Monster.h"
#include "Bullet.h"
USING_NS_CC;


class BaseTower : public Sprite
{
public:
	void buildAnimation(char* name);

	void showUpdateMenu();

	void hideUpdateMenu();

	void showAttackRange();

	void updateTower();//升级防御塔
	virtual void sellTower() {};//出售防御塔
	virtual void removeTower(){}
	virtual bool init();                   //初始化防御塔


	CC_SYNTHESIZE(int, level, Level);//塔的等级

	CC_SYNTHESIZE(float, scope, Scope);//攻击范围

	CC_SYNTHESIZE(float, rate, Rate);//攻速

	CC_SYNTHESIZE(int, damage, Damage);//攻击力

	int speed;      //子弹速度

	CC_SYNTHESIZE(int, buildMoney, BuildMoney);
	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//升级所需金钱
	CC_SYNTHESIZE(int, sellMoney, sellMoney);//售卖金钱

	virtual void showTowerInfo(){}
	bool isUpdateMenuShown;

protected:

	bool InattackRange(Monster* monster);

	float getAngle(Monster* monster);

	Monster* chosenEnemy;
	cocos2d::ui::Button* upgrade = NULL;
	cocos2d::ui::Button* remove = NULL;
	Sprite* attackRange;

};

class Bottle : public BaseTower
{
public:
	CREATE_FUNC(Bottle);

	bool init();

	void update(float dt);

	void addButton();

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	void initEvent();

private:

	void initData();

	void shootWeapon();

	void attack(float dt);
	
};

class Flower : public BaseTower
{
public:

	CREATE_FUNC(Flower);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

protected:

	bool IsAttack;
	
	bool init();

	void update(float dt);

	void attack(float dt);//攻击

	void shootWeapon();

	void initLevel();

	void initEvent();
};

class Star : public BaseTower
{
public:

	CREATE_FUNC(Star);

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

protected:
	bool init();

private:
	
	void initLevel();

	void initEvent();

	void update(float dt);

	void attack(float dt);

	void shootWeapon();
};