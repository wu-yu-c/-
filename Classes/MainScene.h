#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class MainScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene);
private:
	void InitSprite(cocos2d::Sprite*& outSprite, cocos2d::Node* parentNode, const std::string& fileName, float x, float y, int localZOrder);

	bool InitUI();

	void InitEvent();
private:
	cocos2d::ui::Button* click_start_game_button;//�����ʼ��Ϸ��ť
	cocos2d::ui::Button* click_set_button;//������ð�ť
	cocos2d::ui::Button* exit_button;//�˳���ť
};