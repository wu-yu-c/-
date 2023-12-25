#pragma once
#include "cocos2d.h"
//#include "Circle.h"
//#include "Terrain.h"
//#include "BaseMonster.h"
//#include "SoundManager.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class BaseTower : public Sprite{
public:
//	BaseTower();
//	~BaseTower();
//	virtual void updateTower() {};
//	virtual void sellTower();
//	virtual void removeTower();
	virtual bool init() { return 1; };
//	CC_SYNTHESIZE(TowerType, towerType, TowerType);
//	CC_SYNTHESIZE(Terrain*, myTerrain, MyTerrain);
//	CC_SYNTHESIZE(std::string, towerName, TowerName);
//	CC_SYNTHESIZE(int, level, Level);
//	CC_SYNTHESIZE(float, scope, Scope);
//	CC_SYNTHESIZE(float, nextScope, NextScope);
//	CC_SYNTHESIZE(float, rate, Rate);
//	CC_SYNTHESIZE(int, force, Force);
//	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);
//	CC_SYNTHESIZE(int, buildMoney, BuildMoney);
//	virtual void showTowerInfo();
	bool isUpdateMenuShown;
//	virtual void update1() {};
//	virtual void update2() {};
//	virtual void setRallyPoint(Point point) {};
//protected:
//	virtual void checkNearestMonster();
//	//BaseMonster* nearestMonster;
//	bool onTouchBegan(Touch* touch, Event* event);
//	void onTouchEnded(Touch* touch, Event* event);
	virtual void showUpdateMenu() {};
	virtual void hideUpdateMenu() {};
//	Sprite* terrain;
//	void setListener();
	virtual void initLevel(int tag) {};
	virtual void initEvent() {};
	virtual void showAttackRange() {};
	virtual void hideAttackRange() {};
	double range;
	int level;
	int damage;
	double rate;
	cocos2d::ui::Button* update;
	cocos2d::ui::Button* remove;
	Sprite* attackRange;
};

class Bottle : public BaseTower
{
public:
	static BaseTower* createBottleTower(int tag);

	virtual bool myInit(int tag);

	CREATE_FUNC(Bottle);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
protected:
	void initTower(int level);
	//void addTerrain();
	//virtual Bullet* ArtilleryTowerBullet();//´´½¨ÅÚµ¯
	void shoot(float dt);//¹¥»÷
	Sprite* bottle;
	void filledAnimation();//Ìî³äÅÚµ¯¶¯»­
	void fireAnimation();//·¢ÉäÅÚµ¯¶¯»­
	void fire(Point firePosition);//·¢ÉäÅÚµ¯
private:
	void checkNearestMonster();
	void initLevel(int tag)override;
	void initEvent()override;
	void showUpdateMenu();
	void hideUpdateMenu();
	void showAttackRange();
	void hideAttackRange();
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
	//virtual Bullet* ArtilleryTowerBullet();//´´½¨ÅÚµ¯
	void shoot(float dt);//¹¥»÷
	Sprite* flower;
	void filledAnimation();//Ìî³äÅÚµ¯¶¯»­
	void fireAnimation();//·¢ÉäÅÚµ¯¶¯»­
	void fire(Point firePosition);//·¢ÉäÅÚµ¯
private:
	void checkNearestMonster();
	void initLevel(int tag)override;
	void initEvent()override;
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
	//virtual Bullet* ArtilleryTowerBullet();//´´½¨ÅÚµ¯
	void shoot(float dt);//¹¥»÷
	Sprite* star;
	void filledAnimation();//Ìî³äÅÚµ¯¶¯»­
	void fireAnimation();//·¢ÉäÅÚµ¯¶¯»­
	void fire(Point firePosition);//·¢ÉäÅÚµ¯
private:
	void checkNearestMonster();
	void initLevel(int tag)override;
	void initEvent()override;
	void showUpdateMenu();
	void hideUpdateMenu();
	void showAttackRange();
	void hideAttackRange();
};