#include "TowerPanleLayer.h"
bool TowerPanleLayer::init()
{
	if (!Sprite::init())
		return false;

	initUI();

	initEvent();
}

void TowerPanleLayer::initUI()
{
	auto nowScene = Director::getInstance()->getRunningScene();

}

void TowerPanleLayer::initEvent()
{

}