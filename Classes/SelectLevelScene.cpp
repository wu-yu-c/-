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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��������
	auto rootNode = Sprite::create("u031/UI/background.png");
	rootNode->setAnchorPoint(Vec2(0, 0));
	this->addChild(rootNode);
	if (nullptr == rootNode)
		return false;

	//������յ�ͼ
	skyline_button= Button::create("ChooseLevel/skyline.png", "ChooseLevel/skyline.png", "null.png");
	//�˴�δʹ��problemloading������
	skyline_button->setPosition(Vec2(origin.x + 568, origin.y + 320));
	this->addChild(skyline_button, 1);

	//��������������İ�ť
	const char* toolbarHomeFilePath = "ChooseLevel/home_button.png";
	click_main_menu_button = Button::create(toolbarHomeFilePath, toolbarHomeFilePath, "");
	click_main_menu_button->setAnchorPoint(Vec2(0, 0));
	click_main_menu_button->setPosition(Vec2(5, 550));
	click_main_menu_button->setPressedActionEnabled(true);
	//����1��Ŀ���ǽ��������ڱ������ϲ�
	this->addChild(click_main_menu_button, 1);
	if (nullptr == click_main_menu_button)
		return false;

	//����Ұ�ť
	const char* right = "ChooseLevel/right_button.png";
	turn_right = Button::create(right, right, "");
	turn_right->setPosition(Vec2(1136 - 59 / 2 - 11, 320));
	turn_right->setPressedActionEnabled(true);
	//����1��Ŀ���ǽ��������ڱ������ϲ�
	this->addChild(turn_right, 1);
	if (nullptr == turn_right)
		return false;

	//�����ť
	const char* left = "ChooseLevel/left_button.png";
	turn_left = Button::create(left, left, "");
	turn_left->setPosition(Vec2(70 - 59 + 59 / 2, 320));
	turn_left->setPressedActionEnabled(true);
	//����1��Ŀ���ǽ��������ڱ������ϲ�
	this->addChild(turn_left, 1);
	if (nullptr == turn_left)
		return false;

	return true;
}

void SelectLevelScene::InitEvent()
{

	//��ʼ����ҳ��ť
	click_main_menu_button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto mainScene = MainScene::createScene();
			Director::getInstance()->replaceScene(mainScene);
		}
		});

	//��ʼ��ѡ����յ�ͼ��ť
	skyline_button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//�˴���Ҫ��ĳɽ���õ�ͼ��Ŀǰ�ȷ���������
			auto youroperator = MainScene::createScene();
			Director::getInstance()->replaceScene(youroperator);
		}
		});

	//��ʼ����ť
	turn_left->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//�˴���Ҫ��ĳɽ���õ�ͼ��Ŀǰ�ȷ���������
			auto youroperator = MainScene::createScene();
			Director::getInstance()->replaceScene(youroperator);
		}
		});

	//��ʼ���Ұ�ť
	turn_right->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//�˴���Ҫ��ĳɽ���õ�ͼ��Ŀǰ�ȷ���������
			auto youroperator = MainScene::createScene();
			Director::getInstance()->replaceScene(youroperator);
		}
		});
}