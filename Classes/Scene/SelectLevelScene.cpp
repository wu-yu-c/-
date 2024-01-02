#include "Scene/SelectLevelScene.h"
#include "Scene/MainScene.h"
#include"Manager/GameManager.h"
#include "Manager/SoundManager.h"
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

	GameManager::getGame()->maxLevel = 2;

	InitUI();

	InitEvent();

	return true;
}

bool SelectLevelScene::InitUI()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��������
	auto rootNode = Sprite::create("u031/UI/background.png");
	rootNode->setAnchorPoint(Vec2(0, 0));
	this->addChild(rootNode);
	if (nullptr == rootNode)
		return false;

	//����յ�ͼ��Ϊͼ��ӵ�������
	skyline = SkyLine::createLayer();
	this->addChild(skyline);

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
	turn_right->setPosition(Vec2(1136 - 70 / 2 - 11, 320));
	turn_right->setPressedActionEnabled(true);
	//����1��Ŀ���ǽ��������ڱ������ϲ�
	this->addChild(turn_right, 1);
	if (nullptr == turn_right)
		return false;

	//�����ť
	const char* left = "ChooseLevel/left_button.png";
	turn_left = Button::create(left, left, "");
	turn_left->setPosition(Vec2(70 - 59 + 70 / 2, 320));
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
	//��ʼ���Ұ�ť
	turn_right->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (skyline != nullptr) {
				desert = Desert::createLayer();
				this->addChild(desert, 1);
				skyline->removeFromParent();
				skyline = nullptr;
			}
		}
		});
	//��ʼ����ť
	turn_left->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (desert != nullptr) {
				skyline = SkyLine::createLayer();
				this->addChild(skyline, 1);
				desert->removeFromParent();
				desert = nullptr;
			}
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
	//ѡ��ͼƬ
	skyline_button = Button::create("ChooseLevel/skyline.png", "ChooseLevel/skyline.png", "null.png");
	skyline_button->setPosition(Vec2(origin.x + 568, origin.y + 320));
	if (GameManager::getGame()->getResult(1) != 0) {
		char namesize[20] = { 0 };
		sprintf(namesize, "MAP/carrot%d.png", GameManager::getGame()->getResult(1));
		auto carrot = Sprite::create(namesize);
		skyline_button->addChild(carrot);
		carrot->setPosition(skyline_button->getContentSize().width - 10, skyline_button->getContentSize().height / 4);
		carrot->setScale(2.0f);
	}
	this->addChild(skyline_button, 1);
	if (skyline_button == nullptr)
		return false;
	return true;
}

void SkyLine::InitEvent()
{
	//��ʼ��ѡ����յ�ͼ��ť
	skyline_button->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//������ʵ�ͼ
			auto skyMap = SkyMap::createGame();
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

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//ѡ��ͼƬ
	desert_button = Button::create("ChooseLevel/desert.png", "ChooseLevel/desert.png", "null.png");
	desert_button->setPosition(Vec2(origin.x + 568, origin.y + 320));
	this->addChild(desert_button, 1);

	if (GameManager::getGame()->getResult(1) == 0) {
		auto lock = Sprite::create("ChooseLevel/lock.png");
		desert_button->addChild(lock, 1);
		lock->setName("lock");
		lock->setPosition(desert_button->getContentSize().width / 2, desert_button->getContentSize().height / 2);
	}
	else if (GameManager::getGame()->getResult(2) != 0) {
		char namesize[20] = { 0 };
		sprintf(namesize, "MAP/carrot%d.png", GameManager::getGame()->getResult(2));
		auto carrot = Sprite::create(namesize);
		desert_button->addChild(carrot);
		carrot->setPosition(desert_button->getContentSize().width - 10, desert_button->getContentSize().height / 4);
		carrot->setScale(2.0f);
	}

	if (desert_button == nullptr)
		return false;
	return true;
}

void Desert::InitEvent()
{
	//��ʼ��ѡ��ɳĮ��ͼ��ť
	desert_button->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//����ɳĮ��ͼ
			if (GameManager::getGame()->getResult(1)) {
				auto desertMap = DesertMap::createGame();
				Director::getInstance()->pushScene(desertMap);
			}

		}
		});
}
