#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "ui/CocosGUI.h"
class Terrains : public Sprite {

public:
	virtual bool init();
	static Terrains* createTerrain();
	CREATE_FUNC(Terrains);
	void showTowerPanleLayer();
	void hideTowerPanleLayer();
	void showTowerInfo(){}
	void hideTowerInfo(){}
	bool isShow;
	bool isBuilt;
private:
	void initEvent();
	void initUI();
	cocos2d::ui::Button* bottleIcon;
	cocos2d::ui::Button* sunFlowerIcon;
	cocos2d::ui::Button* icedStarIcon;
	void Terrains::removeTowerPanleLayer();
};