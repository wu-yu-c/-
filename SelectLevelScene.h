#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class SelectLevelScene :public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();


	CREATE_FUNC(SelectLevelScene);
private:
	void InitEvent();

	bool InitUI();
private:
	cocos2d::ui::Button* click_main_menu_button;//点击返回主菜单按钮
	cocos2d::ui::Button* turn_left;//左按键
	cocos2d::ui::Button* turn_right;//右按键
	cocos2d::ui::Button* skyline_button;//选择天空地图
};