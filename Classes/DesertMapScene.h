#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"SkyMapScene.h"

class DesertMapScene :public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(DesertMapScene);

private:
	void beginAnimation();

	bool InitUI();

	void InitEvent();

	cocos2d::TMXTiledMap* desertMap;
	cocos2d::TMXObjectGroup* Object;
	cocos2d::ui::Button* stopButton;
	cocos2d::ui::Button* menuButton;
};