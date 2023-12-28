#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class Carrot :public cocos2d::Sprite {
public:
	CREATE_FUNC(Carrot);

	void setLife(int n);

	void BiteCarrot(int n);

private:
	int Life;

	cocos2d::Sprite* life;
	cocos2d::Sprite* carrot;
	cocos2d::ui::Button* updateButton;
	bool isUpdateMenuShown;
	//void showUpdateMenu();
	//void hideUpdateMenu();
	virtual bool init();
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void shakeAnimation(float dt);
	void initEvent();
};