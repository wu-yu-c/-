#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"Monster/Monster.h"
#include "Bullet/Bullet.h"
#include"Tower/Terrains.h"
USING_NS_CC;


class BaseTower : public Sprite
{
public:
	friend class Terrains;

	void buildTower(char* basename,char* towername);

	void buildAnimation(char* basename,char* towername);

	void showUpdateMenu();

	void hideUpdateMenu();

	void showAttackRange();

	void checkMoney(int neddMoney);

	void addButton(int needMoney, int removeMoney);//������������Ͳ����ť
	virtual void sellTower();//���۷�����
	virtual bool init();                   //��ʼ��������
	virtual void initEvent() { }


	CC_SYNTHESIZE(int, level, Level);//���ĵȼ�

	CC_SYNTHESIZE(float, scope, Scope);//������Χ

	CC_SYNTHESIZE(float, rate, Rate);//����

	CC_SYNTHESIZE(int, damage, Damage);//������

	int speed;      //�ӵ��ٶ�

	CC_SYNTHESIZE(int, buildMoney, BuildMoney);
	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//���������Ǯ
	CC_SYNTHESIZE(int, sellMoney, sellMoney);//������Ǯ

	bool isUpdateMenuShown;

protected:

	bool onTouchBegan(Touch* touch, Event* event) { return true; };
	void onTouchEnded(Touch* touch, Event* event);
	bool InattackRange(Monster* monster);
	virtual void updateTower() { } //����������
	float getAngle(Monster* monster);

	void upgradeAnimation();

	void removeAnimation();

	Monster* chosenEnemy;
	cocos2d::ui::Button* upgrade = NULL;
	cocos2d::ui::Button* remove = NULL;
	Sprite* attackRange;
	Sprite* updateSignal = NULL;
};

class Bottle : public BaseTower
{
public:
	CREATE_FUNC(Bottle);

	bool init();

	void update(float dt);

	void initEvent();

private:

	void initData();

	void shootWeapon();

	void attack(float dt);
	
	void updateTower();
};

class Flower : public BaseTower
{
public:
	void initEvent();

	CREATE_FUNC(Flower);

protected:

	bool IsAttack;
	
	bool init();

	void update(float dt);

	void attack(float dt);//����

	void initData();

	void updateTower();
};

class Star : public BaseTower
{
public:
	void initEvent();

	CREATE_FUNC(Star);

protected:
	bool init();

	void initData();
private:

	void attackScope();

	void update(float dt);

	void attack(float dt);

	void shootWeapon();

	void updateTower();
};