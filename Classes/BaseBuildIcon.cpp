#include "BaseBuildIcon.h"
BaseBuildIcon* BaseBuildIcon::createIcon(int type, int money)
{
    auto baseBuildIcon = new BaseBuildIcon();

    if (baseBuildIcon && baseBuildIcon->initIcon(type, money))
    {
        baseBuildIcon->autorelease();
        return baseBuildIcon;
    }
    CC_SAFE_DELETE(baseBuildIcon);
    return NULL;
}

bool BaseBuildIcon::initIcon(int type, int money)
{
	if (!Sprite::init())
	{
		return false;
	}
	
	this->scheduleUpdate();


	return true;
}