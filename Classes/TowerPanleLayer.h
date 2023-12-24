#pragma once
#include "cocos2d.h"
//#include "Circle.h"
#include "Terrains.h"
//#include "BaseBuildIcon.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class TowerPanleLayer : public Sprite
{
public:
	virtual bool init() override;

	CREATE_FUNC(TowerPanleLayer);
	/*
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);*/
	CC_SYNTHESIZE(Terrain*, terrain, MyTerrain);
	void inAnimation();
private:
	void addIcons();
	//void addTempTower(int type);
	void addTower(int type);
	
	Sprite* planesprite;
	//Circle* circle;
	bool isBuilt;

	void initUI();

	void initEvent();
};