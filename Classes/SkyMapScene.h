#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class SkyMapScene :public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SkyMapScene);

private:
	void beginAnimation();

	bool InitUI();

	void InitEvent();

	cocos2d::TMXTiledMap* skyMap;
	cocos2d::TMXObjectGroup* Object;
	cocos2d::ui::Button* stopButton;
	cocos2d::ui::Button* menuButton;
};

class ChooseMenu :public cocos2d::Layer {
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();

	CREATE_FUNC(ChooseMenu);
private:
	bool InitUI();

	void InitEvent();

	cocos2d::ui::Button* restartButton;
	cocos2d::ui::Button* continueButton;
	cocos2d::ui::Button* returnButton;
};