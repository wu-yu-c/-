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
	cocos2d::ui::Button* click_main_menu_button;//����������˵���ť
	cocos2d::ui::Button* turn_left;//�󰴼�
	cocos2d::ui::Button* turn_right;//�Ұ���
	cocos2d::ui::Button* skyline_button;//ѡ����յ�ͼ
	cocos2d::ui::Button* desert_button;//ѡ��ɳĮ��ͼ
};