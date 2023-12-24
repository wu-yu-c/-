#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Carrot :public cocos2d::Sprite {
public:
	CREATE_FUNC(Carrot);

	void setLife(int n);

private:
	int Life;

	cocos2d::Animate* shake;
	cocos2d::Sprite* life;
	cocos2d::Sprite* carrot;

	virtual bool init();

	virtual void Move(float dt);

	void InitAnimation();

};