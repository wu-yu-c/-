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
	virtual void updateTower() {};//����������
	virtual void sellTower() {};//���۷�����
	virtual void removeTower(){}
	virtual bool init() { return 1; };//��ʼ��������
	CC_SYNTHESIZE(TowerType, towerType, TowerType);//����
	CC_SYNTHESIZE(Terrain*, myTerrain, MyTerrain);//�����
	CC_SYNTHESIZE(std::string, towerName, TowerName);//����
	CC_SYNTHESIZE(int, level, Level);//���ĵȼ�
	CC_SYNTHESIZE(float, scope, Scope);//������Χ
	CC_SYNTHESIZE(float, nextScope, NextScope);//������Χ
	CC_SYNTHESIZE(float, rate, Rate);//����
	CC_SYNTHESIZE(int, force, Force);//������
	CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//���������Ǯ
	CC_SYNTHESIZE(int, buildMoney, BuildMoney);//������Ǯ
	virtual void showTowerInfo(){}
	bool isUpdateMenuShown;//
	virtual void setRallyPoint(Point point) {};
protected:
	virtual void checkNearestMonster() {};//��⸽������
	Monster* nearestMonster;//�����ĵ���
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	virtual void showUpdateMenu() {};
	virtual void hideUpdateMenu() {};
	Sprite* terrain;//�����Ľ����
	void setListener();//���ü�����
	cocos2d::ui::Button* update;
	cocos2d::ui::Button* remove;
	Sprite* attackRange;
	int damage;
};

//class BaseBottleTower : public BaseTower
//{
//protected:
//	Sprite* bottle;//ƿ������
//	void initTower(int level);//��ʼ������
//	void addTerrain();//��������ӣ������Ǹ������������Ǹ����ǹ����ĵ��棬��ͬ��ͼ�в�ͬ������~��
//	virtual void BottleTowerBullet();//�����ڵ�
//	virtual void shoot(float dt);//�����ڵ�
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
	//virtual Bullet* ArtilleryTowerBullet();//�����ڵ�
	void shoot(float dt);//����
	Sprite* bottle;
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