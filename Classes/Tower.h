#pragma once
#include "cocos2d.h"
//#include "Circle.h"
//#include "Terrain.h"
//#include "BaseMonster.h"
//#include "SoundManager.h"
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
	BaseTower() {};
	~BaseTower() {};
	virtual void updateTower() {};//升级防御塔
	virtual void sellTower() {};//出售防御塔
	virtual void removeTower(){}
	virtual bool init() { return 1; };//初始化防御塔
	CC_SYNTHESIZE(TowerType, towerType, TowerType);//类型
	CC_SYNTHESIZE(Terrain*, myTerrain, MyTerrain);//建造点
	CC_SYNTHESIZE(std::string, towerName, TowerName);//塔名
	CC_SYNTHESIZE(int, level, Level);//塔的等级
	CC_SYNTHESIZE(float, scope, Scope);//攻击范围
	CC_SYNTHESIZE(float, nextScope, NextScope);//升级后范围
	CC_SYNTHESIZE(float, rate, Rate);//攻速
	CC_SYNTHESIZE(int, force, Force);//攻击力
	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//升级所需金钱
	CC_SYNTHESIZE(int, buildMoney, BuildMoney);//售卖金钱
	virtual void showTowerInfo(){}
	bool isUpdateMenuShown;//
	virtual void setRallyPoint(Point point) {};
protected:
	virtual void checkNearestMonster() {};//检测附近敌人
	Monster* nearestMonster;//附近的敌人
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	virtual void showUpdateMenu() {};
	virtual void hideUpdateMenu() {};
	Sprite* terrain;//该塔的建造点
	void setListener();//设置监听器
	cocos2d::ui::Button* update;
	cocos2d::ui::Button* remove;
	Sprite* attackRange;
	int damage;
};

//class BaseBottleTower : public BaseTower
//{
//protected:
//	Sprite* bottle;//瓶子炮塔
//	void initTower(int level);//初始化炮塔
//	void addTerrain();//添加塔坯子（就是那个都是塔下面那个都是弓箭的地面，不同地图有不同的坯子~）
//	virtual void BottleTowerBullet();//生成炮弹
//	virtual void shoot(float dt);//发射炮弹
//};
class Bottle : public BaseTower
{
public:
	static BaseTower* createBottleTower(int tag);

	virtual bool myInit(int tag);

	CREATE_FUNC(Bottle);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void Spin(float dt);
protected:
	void initTower(int level);
	//void addTerrain();
	//virtual Bullet* ArtilleryTowerBullet();//创建炮弹
	void shoot(float dt);//攻击
	Sprite* bottle;
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
	void shoot();
	BottleBullet* bullet;
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