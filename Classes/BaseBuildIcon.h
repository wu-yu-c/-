#pragma once
#include "cocos2d.h"

USING_NS_CC;

class BaseBuildIcon : public Sprite
{
public:

	virtual bool init();
	virtual bool initIcon(int type, int money);
	static BaseBuildIcon* createIcon(int type, int money);

	CREATE_FUNC(BaseBuildIcon);
	virtual void setSelected();
	virtual void setNotSelected();
	virtual void setNotEnoughMoney();
	virtual void setEnoughMoney();
	virtual void setUpdateMoney(int money);
	Sprite* baseIcon;
private:

protected:
	CC_SYNTHESIZE(bool, isAble, IsAble);
	CC_SYNTHESIZE(int, type, Type);
	CC_SYNTHESIZE(bool, isSelected, IsSelected);
	CC_SYNTHESIZE(int, money, Money);
	void update(float dt);
	Sprite* okIcon;
	Sprite* priceIcon;
	Label* priceLabel;
};

class SunFlower :public BaseBuildIcon {
public:
	static BaseBuildIcon* createSunFlowerTower(int type, int money);

	virtual bool init();
	virtual bool initIcon(int type, int money);
	SunFlower* sunflower;
};

class Bottle :public BaseBuildIcon {
public:
	static BaseBuildIcon* createBottleTower(int type, int money);

	virtual bool init();
	virtual bool initIcon(int type, int money);
};

class IcedStar :public BaseBuildIcon {
public:
	static BaseBuildIcon* createIcedStarTower(int type, int money);

	virtual bool init();
	virtual bool initIcon(int type, int money);
};