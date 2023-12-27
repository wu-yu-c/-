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

	void updateTower();//升级防御塔
	virtual void sellTower() {};//出售防御塔
	virtual void removeTower() {}
	virtual bool init();                   //初始化防御塔
	CC_SYNTHESIZE(TowerType, towerType, TowerType);//类型
	CC_SYNTHESIZE(Terrain*, myTerrain, MyTerrain);//建造点
	CC_SYNTHESIZE(std::string, towerName, TowerName);//塔名
	CC_SYNTHESIZE(int, level, Level);//塔的等级
	CC_SYNTHESIZE(float, scope, Scope);//攻击范围
	CC_SYNTHESIZE(float, nextScope, NextScope);//升级后范围
	CC_SYNTHESIZE(float, rate, Rate);//攻速
	CC_SYNTHESIZE(int, force, Force);//攻击力
	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//升级所需金钱
	CC_SYNTHESIZE(int, sellMoney, sellMoney);//售卖金钱
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
	//virtual Bullet* ArtilleryTowerBullet();//创建炮弹
	void shoot(float dt);//攻击
	Sprite* flower;
	void filledAnimation();//填充炮弹动画
	void fireAnimation();//发射炮弹动画
	void fire(Point firePosition);//发射炮弹
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
	//virtual Bullet* ArtilleryTowerBullet();//创建炮弹
	void shoot(float dt);//攻击
	Sprite* star;
	void filledAnimation();//填充炮弹动画
	void fireAnimation();//发射炮弹动画
	void fire(Point firePosition);//发射炮弹
private:
	void checkNearestMonster() {};
	void initLevel(int tag);
	void initEvent();
	void showUpdateMenu();
	void hideUpdateMenu();
	void showAttackRange();
	void hideAttackRange();
};