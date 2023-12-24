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
	bool isTowerPanleLayerShown;

	bool isBuilt;
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	Sprite* terrain;
private:
	void initEvent();

	cocos2d::ui::Button* bottleIcon;
	cocos2d::ui::Button* planeIcon;
	cocos2d::ui::Button* icedStarIcon;
};