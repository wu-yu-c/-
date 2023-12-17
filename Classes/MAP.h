#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include<vector>

class MAP :public cocos2d::Scene {
public:

	CREATE_FUNC(MAP);

	void beginAnimation();

	bool InitUI();

	void InitEvent();

	cocos2d::TMXTiledMap* tilemap;
	cocos2d::TMXObjectGroup* Object;
	cocos2d::ui::Button* stopButton;
	cocos2d::ui::Button* menuButton;
	cocos2d::Sprite* birthPlace;
	cocos2d::Sprite* carrot;
	std::vector<cocos2d::Node*> Path;
};

class SkyMapScene :public MAP {
public:
	static MAP* createMap();

	CREATE_FUNC(SkyMapScene);
};

class DesertMapScene :public MAP {
public:
	static MAP* createMap();

	CREATE_FUNC(DesertMapScene);

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