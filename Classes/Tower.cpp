//#include "Tower.h"
//#include "MAP.h"
//Tower::Tower() :isUpdateMenuShown(false) {};
//
//Tower::~Tower() {};
//
//bool Tower::init()
//{
//	if (!Sprite::init())
//		return false;
//	isUpdateMenuShown = false;
//	return true;
//}
//
//bool Tower::onTouchBegan(Touch* touch, Event* event)
//{
//	return true;
//}
//
//void Tower::onTouchEnded(Touch* touch, Event* event)
//{
//	auto target = static_cast<Sprite*>(event->getCurrentTarget());
//
//	Point locationInNode = target->convertTouchToNodeSpace(touch);
//
//	Size size = target->getContentSize();
//	Rect rect = Rect(0, 0, size.width, size.height);
//	if (rect.containsPoint(locationInNode))
//	{
//		//static_cast<MAP*>(this->getParent()->getParent())->playerState->showTowerInfo(getTowerType());
//		if (isUpdateMenuShown)
//		{
//			hideUpdateMenu();
//		}
//		else {
//			showUpdateMenu();
//		}
//	}
//	else {
//		hideUpdateMenu();
//	}
//}
//
