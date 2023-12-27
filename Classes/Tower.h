#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Monster.h"
#include "Bullet.h"
USING_NS_CC;

typedef enum {
	Bottle_1, Bottle_2, Bottle_3,
	Flower_1, Flower_2, Flower_3,
	Star_1, Star_2, Star_3
}TowerType;


class BaseTower : public Sprite
{
public:
	void buildAnimation(char* name, int i);

	void InitBase(int i);

	void showUpdateMenu();

	void hideUpdateMenu();

	void showAttackRange();

	void updateTower();//����������
	virtual void sellTower() {};//���۷�����
	virtual void removeTower() {}
	virtual bool init();                   //��ʼ��������
	CC_SYNTHESIZE(TowerType, towerType, TowerType);//����
	CC_SYNTHESIZE(Terrain*, myTerrain, MyTerrain);//�����
	CC_SYNTHESIZE(std::string, towerName, TowerName);//����
	CC_SYNTHESIZE(int, level, Level);//���ĵȼ�
	CC_SYNTHESIZE(float, scope, Scope);//������Χ
	CC_SYNTHESIZE(float, nextScope, NextScope);//������Χ
	CC_SYNTHESIZE(float, rate, Rate);//����
	CC_SYNTHESIZE(int, force, Force);//������
	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//���������Ǯ
	CC_SYNTHESIZE(int, sellMoney, sellMoney);//������Ǯ
	virtual void showTowerInfo() {}
	bool isUpdateMenuShown;//

protected:

	bool InattackRange(Monster* monster);

	float getAngle(Monster* monster);

	Monster* chosenEnemy;
	cocos2d::ui::Button* upgrade;
	cocos2d::ui::Button* remove;
	Sprite* attackRange;
	int damage;

};

class Bottle : public BaseTower
{
public:
	CREATE_FUNC(Bottle);

	bool init();

	void update(float dt);

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

private:

	void initLevel();
	void initEvent();

	void shootWeapon();

	void attack(float dt);

};

class Flower : public BaseTower
{
public:
	static BaseTower* createFlowerTower(int tag);

	virtual bool myInit(int tag);

	CREATE_FUNC(Flower);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
protected:
	void initTower(int level);
	//void addTerrain();
	//virtual Bullet* ArtilleryTowerBullet();//�����ڵ�
	void shoot(float dt);//����
	Sprite* flower;
	void filledAnimation();//����ڵ�����
	void fireAnimation();//�����ڵ�����
	void fire(Point firePosition);//�����ڵ�
private:
	void checkNearestMonster() {};
	void initLevel(int tag);
	void initEvent();
	void showUpdateMenu();
	void hideUpdateMenu();
	void showAttackRange();
	void hideAttackRange();
};

class Star : public BaseTower
{
public:
	static BaseTower* createStarTower(int tag);

	virtual bool myInit(int tag);

	CREATE_FUNC(Star);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
protected:
	void initTower(int level);
	//void addTerrain();
	//virtual Bullet* ArtilleryTowerBullet();//�����ڵ�
	void shoot(float dt);//����
	Sprite* star;
	void filledAnimation();//����ڵ�����
	void fireAnimation();//�����ڵ�����
	void fire(Point firePosition);//�����ڵ�
private:
	void checkNearestMonster() {};
	void initLevel(int tag);
	void initEvent();
	void showUpdateMenu();
	void hideUpdateMenu();
	void showAttackRange();
	void hideAttackRange();
};