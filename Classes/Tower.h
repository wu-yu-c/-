//#pragma once
//#include "cocos2d.h"
//USING_NS_CC;
//
//class Terrain : public Sprite {
//
//public:
//	virtual bool init(int type);
//	static Terrain* createTerrain(int type);
//	void showUpdateMenu();
//	void hideUpdateMenu();
//	Sprite* terrain;
//	bool onTouchBegan(Touch* touch, Event* event);
//	void onTouchEnded(Touch* touch, Event* event);
//	bool isUpdateMenuShown;
//};
//
//class Tower :public cocos2d::Sprite {
//public:
//	Tower();
//	~Tower();
//	virtual void sellTower();
//	virtual void updateTower() {};
//	virtual bool init();
//	bool isUpdateMenuShown;
//	virtual void showTowerInfo();
//	virtual void hideTowerInfo();
//	virtual void showUpdateMenu() {};
//	virtual void hideUpdateMenu();
//	virtual void setAvaiablePoint() {};
//protected:
//	int damage;
//	double attack_speed;
//	double range;
//	virtual void checkNearestMonster();
//	bool onTouchBegan(Touch* touch, Event* event);
//	void onTouchEnded(Touch* touch, Event* event);
//	Sprite* terrain;
//	void setListener();
//};
//
//class BottleTower_1 :public Tower {
//
//};
//class BottleTower_2 :public Tower {
//
//};
//class BottleTower_3 :public Tower {
//
//};