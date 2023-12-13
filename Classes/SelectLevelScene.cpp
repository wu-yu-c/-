#include "SelectLevelScene.h"
#include "MainScene.h"
USING_NS_CC;
using namespace cocos2d::ui;

cocos2d::Scene* SelectLevelScene::createScene()
{
	return SelectLevelScene::create();
}

bool SelectLevelScene::init()
{
	if (!Scene::init())
		return false;

	InitUI();

	InitEvent();

	return true;
}

bool SelectLevelScene::InitUI()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建背景
	auto rootNode = Sprite::create("u031/UI/background.png");
	rootNode->setAnchorPoint(Vec2(0, 0));
	this->addChild(rootNode);
	if (nullptr == rootNode)
		return false;

	//把天空地图作为图层加到界面中
	auto skyline = SkyLine::create();
	this->addChild(skyline);

	//创建返回主界面的按钮
	const char* toolbarHomeFilePath = "ChooseLevel/home_button.png";
	click_main_menu_button = Button::create(toolbarHomeFilePath, toolbarHomeFilePath, "");
	click_main_menu_button->setAnchorPoint(Vec2(0, 0));
	click_main_menu_button->setPosition(Vec2(5, 550));
	click_main_menu_button->setPressedActionEnabled(true);
	//参数1的目的是将其设置在背景的上层
	this->addChild(click_main_menu_button, 1);
	if (nullptr == click_main_menu_button)
		return false;

	//添加右按钮
	const char* right = "ChooseLevel/right_button.png";
	turn_right = Button::create(right, right, "");
	turn_right->setPosition(Vec2(1136 - 70 / 2 - 11, 320));
	turn_right->setPressedActionEnabled(true);
	//参数1的目的是将其设置在背景的上层
	this->addChild(turn_right, 1);
	if (nullptr == turn_right)
		return false;

	//添加左按钮
	const char* left = "ChooseLevel/left_button.png";
	turn_left = Button::create(left, left, "");
	turn_left->setPosition(Vec2(70 - 59 + 70 / 2, 320));
	turn_left->setPressedActionEnabled(true);
	//参数1的目的是将其设置在背景的上层
	this->addChild(turn_left, 1);
	if (nullptr == turn_left)
		return false;

	return true;
}

void SelectLevelScene::InitEvent()
{

	//初始化首页按钮
	click_main_menu_button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto mainScene = MainScene::createScene();
			Director::getInstance()->replaceScene(mainScene);
		}
		});

	//初始化左按钮
	turn_left->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//获取当前场景
			auto currentScene = Director::getInstance()->getRunningScene();
			// 根据图层名称查找要移除的图层
			auto currentLayer = currentScene->getChildByName("ChooseLevel/desert.png");
			// 如果找到了要移除的图层，则移除它
			if (currentLayer)
				currentLayer->removeFromParent();
			// 创建并添加天际图层
			auto newLayer = SkyLine::createLayer();
			currentScene->addChild(newLayer);
		}
		});

	//初始化右按钮
	turn_right->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//获取当前场景
			auto currentScene = Director::getInstance()->getRunningScene();
			// 根据图层名称查找要移除的图层
			auto currentLayer = currentScene->getChildByName("ChooseLevel/skyline.png");
			// 如果找到了要移除的图层，则移除它
			if (currentLayer)
				currentLayer->removeFromParent();
			// 创建并添加沙漠图层
			auto newLayer = Desert::createLayer();
			currentScene->addChild(newLayer);
		}
		});
}

cocos2d::Layer* SkyLine::createLayer()
{
	return SkyLine::create();
}

bool SkyLine::init()
{
	if (!Layer::init())
		return false;

	InitUI();

	InitEvent();

	return true;
}

bool SkyLine::InitUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//选关图片
	skyline_button = Button::create("ChooseLevel/skyline.png", "ChooseLevel/skyline.png", "null.png");
	//此处未使用problemloading检查错误
	skyline_button->setPosition(Vec2(origin.x + 568, origin.y + 320));
	this->addChild(skyline_button, 1);
	if (skyline_button == nullptr)
		return false;
	return true;
}

void SkyLine::InitEvent()
{
	//初始化选择天空地图按钮
	skyline_button->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//进入天际地图
			skyMap = SkyMapScene::createScene();
			Director::getInstance()->pushScene(skyMap);
		}
		});
}

cocos2d::Layer* Desert::createLayer()
{
	return Desert::create();
}

bool Desert::init()
{
	if (!Layer::init())
		return false;

	InitUI();

	InitEvent();

	return true;
}

bool Desert::InitUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//选关图片
	desert_button = Button::create("ChooseLevel/desert.png", "ChooseLevel/desert.png", "null.png");
	//此处未使用problemloading检查错误
	desert_button->setPosition(Vec2(origin.x + 568, origin.y + 320));
	this->addChild(desert_button, 1);
	if (desert_button == nullptr)
		return false;
	return true;
}

void Desert::InitEvent()
{
	//初始化选择沙漠地图按钮
	desert_button->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//进入沙漠地图
			desertMap = DesertMapScene::createScene();			
			Director::getInstance()->pushScene(desertMap);
		}
		});
}
