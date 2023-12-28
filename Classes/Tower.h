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

	void updateTower();//����������
	virtual void sellTower() {};//���۷�����
	virtual void removeTower(){}
	virtual bool init();                   //��ʼ��������


	CC_SYNTHESIZE(int, level, Level);//���ĵȼ�

	CC_SYNTHESIZE(float, scope, Scope);//������Χ

	CC_SYNTHESIZE(float, rate, Rate);//����

	CC_SYNTHESIZE(int, damage, Damage);//������

	int speed;      //�ӵ��ٶ�

	CC_SYNTHESIZE(int, buildMoney, BuildMoney);
	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//���������Ǯ
	CC_SYNTHESIZE(int, sellMoney, sellMoney);//������Ǯ

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

	void attack(float dt);//����

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