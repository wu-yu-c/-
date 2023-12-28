#include "Tower.h"
#include "cocos2d.h"
#include "Terrains.h"
#include "MAP.h"
#include <vector>
#include"GameManager.h"
#include "Bullet.h"
#include<math.h>
using namespace cocos2d::ui;

char basename[3][50] = {
	"Bottle/Bottle_3.png",
	"Flower/level1.png"
	"Star/level1_base.png"
};

bool BaseTower::init() {

	if (!Sprite::init())
		return false;

	chosenEnemy = NULL;

	return true;
}

void BaseTower::buildAnimation(char* name) {

	char namesize[30] = { 0 };
	auto animation = Animation::create();
	for (int i = 1; i <= 4; i++) {
		sprintf(namesize, "MAP/smoke_%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}
	animation->addSpriteFrameWithFile(name);

	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	auto build = Animate::create(animation);

	runAction(build);
}

/*有时间搞升级动画*/
void BaseTower::updateTower() {

}

void BaseTower::showAttackRange()
{
	// 显示攻击范围的圆形精灵
	attackRange->setVisible(true);
	attackRange->setScale(0.1f);
	attackRange->runAction(ScaleTo::create(0.2f, scope));

}

void BaseTower::showUpdateMenu() {

	isUpdateMenuShown = true;
	showAttackRange();
	upgrade->setVisible(true);
	remove->setVisible(true);

}

void BaseTower::hideUpdateMenu() {

	isUpdateMenuShown = false;
	attackRange->setVisible(false);
	upgrade->setVisible(false);
	remove->setVisible(false);

}

bool BaseTower::InattackRange(Monster* monster) {

	Point monsterPos = monster->getParent()->convertToWorldSpace(monster->getPosition());
	Point Pos = getParent()->convertToWorldSpace(getPosition());

	float distance = Pos.distance(monsterPos);

	if (distance < attackRange->getContentSize().width / 2 * scope || distance < attackRange->getContentSize().height / 2 * scope)
		return true;
	else
		return false;

}

float BaseTower::getAngle(Monster* monster) {


	Point to = monster->getParent()->convertToWorldSpace(monster->getPosition());
	Point from = getParent()->convertToWorldSpace(getPosition());

	float y = to.y - from.y;
	float x = to.x - from.x;

	float angle = atan(y / x);
	float degrees = CC_RADIANS_TO_DEGREES(angle);

	if (x > 0 && y > 0)
		return -degrees;
	else if (x > 0 && y < 0)
		return -degrees;
	else if (x < 0 && y>0)
		return -degrees - 180;
	else
		return -degrees - 180;

}

/**********************************************************/

void Bottle::attack(float dt) {

	if (chosenEnemy != NULL) {

		auto animation = Animation::create();

		char namesize[30] = { 0 };

		sprintf(namesize, "Bottle/Bottle%d1.png", level);
		animation->addSpriteFrameWithFile(namesize);
		sprintf(namesize, "Bottle/Bottle%d2.png", level);
		animation->addSpriteFrameWithFile(namesize);
		sprintf(namesize, "Bottle/Bottle%d3.png", level);
		animation->addSpriteFrameWithFile(namesize);
		sprintf(namesize, "Bottle/Bottle%d1.png", level);
		animation->addSpriteFrameWithFile(namesize);

		animation->setLoops(1);
		animation->setDelayPerUnit(0.1f);

		auto shoot = Animate::create(animation);
		runAction(Sequence::create(shoot
			, CallFuncN::create(CC_CALLBACK_0(Bottle::shootWeapon, this))
			, NULL));

	}

}

void Bottle::shootWeapon() {

	if (chosenEnemy != NULL) {

		BottleBullet* bullet = BottleBullet::create();

		Point src = chosenEnemy->convertToNodeSpace(getParent()->convertToWorldSpace(getPosition()));

		Point dst = Vec2(chosenEnemy->getContentSize().width / 2, chosenEnemy->getContentSize().height / 2);

		chosenEnemy->addChild(bullet);
		bullet->setPosition(src);
		bullet->setRotation(getAngle(chosenEnemy));

		float dur = src.distance(dst) / speed;

		if (chosenEnemy->IsReverse)
			bullet->setRotation(180 - getRotation());


		bullet->runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_0(BottleBullet::shoot, bullet, level))
			, MoveTo::create(dur, dst)
			, CallFuncN::create(CC_CALLBACK_0(BottleBullet::removeFromParent, bullet))
			, CallFuncN::create(CC_CALLBACK_0(Monster::getHurt, chosenEnemy, damage, Boom))
			, NULL));

	}
}

bool Bottle::init() {

	if (!Sprite::init())
		return false;

	buildAnimation("Bottle/Bottle11.png");

	initData();

	scheduleUpdate();

	schedule(schedule_selector(Bottle::attack), rate);

	return true;

}

void Bottle::initData()
{
	//初始化数据
	level = 1;
	rate = 1.0f;
	scope = 0.8f;
	speed = 300;
	damage = 10;
	buildMoney = 100;
	sellMoney = 80;
	updateMoney = 180;
	attackRange = cocos2d::Sprite::create("GamePlay/range.png");
	attackRange->setPosition(40, 40);
	attackRange->setScale(scope);
	attackRange->setVisible(false);
	isUpdateMenuShown = false;

}

void Bottle::addButton()
{
	auto nowScene = Director::getInstance()->getRunningScene();
	auto position = getParent()->getPosition();
	//添加升级按钮
	upgrade = Button::create("Money/update_180.png", "Money/update_180.png", "");
	upgrade->setPosition(position + Vec2(0, 70)); //+Vec2(40, 110)
	upgrade->setPressedActionEnabled(true);
	upgrade->setVisible(false);
	nowScene->addChild(upgrade, 3);

	//添加拆除按钮
	remove = Button::create("Money/remove_80.png", "Money/remove_80.png", "");
	remove->setPosition(position + Vec2(0, -70));// +Vec2(40, -30)
	remove->setPressedActionEnabled(true);
	remove->setVisible(false);
	nowScene->addChild(remove, 3);
}


//添加事件监听器
void Bottle::initEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Bottle::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Bottle::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	getParent()->addChild(attackRange);

	upgrade->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (level == 1) {
				level++;
				damage += 10;
				sellMoney = 224;
				rate = 0.7f;
				scope = 1.0f;
				speed = 400;
				GameManager::getGame()->Money -= updateMoney;
				updateMoney = 220;
				upgrade->loadTextures("Money/update_220.png", "Money/update_220.png");
				setTexture("Bottle/Bottle21.png");
				remove->loadTextures("Money/remove_224.png", "Money/remove_224.png");
			}
			else if (level == 2) {
				level++;
				damage += 10;
				sellMoney = 432;
				rate = 0.4f;
				scope = 1.2f;
				speed = 500;
				GameManager::getGame()->Money -= updateMoney;
				upgrade->loadTextures("Money/update_max.png", "Money/update_max.png");
				setTexture("Bottle/Bottle31.png");
				remove->loadTextures("Money/remove_432.png", "Money/remove_432.png");
				upgrade->setPressedActionEnabled(false);
			}
			hideUpdateMenu();
			unschedule(schedule_selector(Bottle::attack));
			schedule(schedule_selector(Bottle::attack), rate);
			attackRange->setScale(scope);
		}
		});

	remove->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			/*此处应将基座设为可触摸*/
			auto parent = static_cast<Terrains*>(getParent());
			GameManager::getGame()->Money += sellMoney;
			parent->setTexture("GamePlay/select.png");
			parent->setOpacity(0);
			parent->setIsShow(0);
			parent->setIsBuilt(0);
			upgrade->removeFromParent();
			remove->removeFromParent();
			removeFromParentAndCleanup(true);
		}
		});

}

bool Bottle::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

//按下瓶子炮塔时，显示或关闭升级菜单
void Bottle::onTouchEnded(Touch* touch, Event* event)
{
	//转换坐标系
	Point locationInNode = convertTouchToNodeSpace(touch);

	Size size = getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode))
	{
		if (isUpdateMenuShown)
			hideUpdateMenu();
		else
			showUpdateMenu();
	}
	else {
		hideUpdateMenu();
	}
}


void Bottle::update(float dt) {

	if (GameManager::getGame()->currentMonster.contains(chosenEnemy) == false)
		chosenEnemy = NULL;

	/*有攻击目标*/
	if (chosenEnemy) {

		setRotation(getAngle(chosenEnemy));

		if (!InattackRange(chosenEnemy)) {
			chosenEnemy = NULL;
		}

	}
	else {

		auto monsters = GameManager::getGame()->currentMonster;
		Vector<Monster*>::iterator it = monsters.begin();
		for (; it != monsters.end(); it++) {
			if (InattackRange((*it))) {
				chosenEnemy = (*it);
				break;
			}
		}

	}

}

/**********************************************************/

bool Flower::init() {

	if (!Sprite::init())
		return false;

	buildAnimation("Flower/level1_bg.png");

	
	initLevel();

	initEvent();

	scheduleUpdate();

	schedule(schedule_selector(Flower::attack), rate);

	return true;

}

void Flower::initLevel()
{

	//添加升级按钮
	upgrade = Button::create("Money/update_220.png", "Money/update_220.png", "");
	upgrade->setPosition(Vec2(40, 110));
	upgrade->setPressedActionEnabled(true);
	upgrade->setVisible(false);
	this->addChild(upgrade, 3);

	//添加拆除按钮
	remove = Button::create("Money/remove_144.png", "Money/remove_144.png", "");
	remove->setPosition(Vec2(37,-40));
	remove->setPressedActionEnabled(true);
	remove->setVisible(false);
	this->addChild(remove, 3);

	//初始化数据
	IsAttack = false;
	level = 1;
	rate = 2.0f;
	scope = 0.8f;
	speed = 300;
	damage = 10;
	attackRange = cocos2d::Sprite::create("GamePlay/range.png");
	addChild(attackRange);
	attackRange->setPosition(40, 40);
	attackRange->setScale(scope);
	attackRange->setVisible(false);
	isUpdateMenuShown = false;
}

//添加事件监听器
void Flower::initEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Flower::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Flower::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	upgrade->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (level == 1) {
				level++;
				damage += 10;
				upgrade->loadTextures("Money/update_260.png", "Money/update_260.png");
				setTexture("Flower/level2_bg.png");
				remove->loadTextures("Money/remove_336.png", "Money/remove_336.png");
			}
			else if (level == 2) {
				level++;
				damage += 10;
				upgrade->loadTextures("Money/update_max.png", "Money/update_max.png");
				setTexture("Flower/level3_bg3.png");
				remove->loadTextures("Money/remove_560.png", "Money/remove_560.png");
			}
		}
		});

	remove->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{

			GameManager::getGame()->Money += sellMoney;
			removeFromParent();

		}
		});

}

bool Flower::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void Flower::onTouchEnded(Touch* touch, Event* event)
{
	//转换坐标系
	Point locationInNode = convertTouchToNodeSpace(touch);

	Size size = getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode))
	{
		if (isUpdateMenuShown)
			hideUpdateMenu();
		else
			showUpdateMenu();
	}
	else {
		hideUpdateMenu();
	}
}

void Flower::attack(float dt) {

	if (IsAttack) {

		if (getRotation() == 0)
			setRotation(30);
		else
			setRotation(0);

		char namesize[30] = { 0 };
		sprintf(namesize, "Flower/PFlower%d.png", level);

		auto bullet = Sprite::create("Flower/PFlower1.png");

		getParent()->addChild(bullet);
		bullet->setPosition(getParent()->getContentSize().width / 2, getParent()->getContentSize().height / 2);

		bullet->runAction(Sequence::create(ScaleTo::create(0.3f, scope+0.8)
			,DelayTime::create(0.2f)
			,CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent,bullet))
			, NULL));

		auto monsters = GameManager::getGame()->currentMonster;
		Vector<Monster*>::iterator it = monsters.begin();
		for (; it != monsters.end(); it++) {
			if (InattackRange(*it))
				(*it)->getHurt(damage, Burn);
		}

	}

}

void Flower::update(float dt) {

	if (GameManager::getGame()->currentMonster.contains(chosenEnemy) == false)
		chosenEnemy = NULL;

	/*有攻击目标*/
	if (chosenEnemy) {

		IsAttack = true;

		if (!InattackRange(chosenEnemy)) {
			chosenEnemy = NULL;
		}

	}
	else {

		auto monsters = GameManager::getGame()->currentMonster;
		Vector<Monster*>::iterator it = monsters.begin();
		for (; it != monsters.end(); it++) {
			if (InattackRange((*it))) {
				chosenEnemy = (*it);
				break;
			}
		}
		if (it == monsters.end())
			IsAttack = false;

	}

}

/****************************************************/

bool Star::init() {

	if (!Sprite::init())
		return false;

	buildAnimation("Star/level1.png");


	initLevel();

	initEvent();

	scheduleUpdate();

	schedule(schedule_selector(Star::attack), rate);

	return true;

}

void Star::update(float dt) {

	if (GameManager::getGame()->currentMonster.contains(chosenEnemy) == false)
		chosenEnemy = NULL;

	/*有攻击目标*/
	if (chosenEnemy) {

		if (!InattackRange(chosenEnemy)) {
			chosenEnemy = NULL;
		}

	}
	else {

		auto monsters = GameManager::getGame()->currentMonster;
		Vector<Monster*>::iterator it = monsters.begin();
		for (; it != monsters.end(); it++) {
			if (InattackRange((*it))) {
				chosenEnemy = (*it);
				break;
			}
		}

	}

}

void Star::shootWeapon() {

	if (chosenEnemy != NULL) {

		StarBullet* bullet = StarBullet::create();

		Point src = chosenEnemy->convertToNodeSpace(getParent()->convertToWorldSpace(getPosition()));

		Point dst = Vec2(chosenEnemy->getContentSize().width / 2, chosenEnemy->getContentSize().height / 2);

		chosenEnemy->addChild(bullet);
		bullet->setPosition(src);
		bullet->setRotation(getAngle(chosenEnemy));

		float dur = src.distance(dst) / speed;

		bullet->runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_0(StarBullet::shoot, bullet, level))
			, MoveTo::create(dur, dst)
			, CallFuncN::create(CC_CALLBACK_0(BottleBullet::removeFromParent, bullet))
			,CallFuncN::create(CC_CALLBACK_0(Monster::getHurt,chosenEnemy,damage,Ice))
			, NULL));

	}

}

void Star::attack(float dt) {

	if (chosenEnemy != NULL) {

		auto rotate = RotateTo::create(0.05f, getAngle(chosenEnemy));
		auto rerotate = RotateTo::create(0.05f, 0);

		runAction(Sequence::create(rotate
			, rerotate
			,CallFuncN::create(CC_CALLBACK_0(Star::shootWeapon,this))
			,NULL));

	}
}

void Star::initLevel()
{

	//添加升级按钮
	upgrade = Button::create("Money/update_220.png", "Money/update_220.png", "");
	upgrade->setPosition(Vec2(35,100));
	upgrade->setPressedActionEnabled(true);
	upgrade->setVisible(false);
	this->addChild(upgrade, 3);

	//添加拆除按钮
	remove = Button::create("Money/remove_144.png", "Money/remove_144.png", "");
	remove->setPosition(Vec2(30,-40));
	remove->setPressedActionEnabled(true);
	remove->setVisible(false);
	this->addChild(remove, 3);

	//初始化数据
	level = 1;
	rate = 1.0f;
	scope = 0.8f;
	speed = 300;
	damage = 10;
	attackRange = cocos2d::Sprite::create("GamePlay/range.png");
	addChild(attackRange);
	attackRange->setPosition(40, 40);
	attackRange->setScale(scope);
	attackRange->setVisible(false);
	isUpdateMenuShown = false;
}

//添加事件监听器
void Star::initEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Star::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Star::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	upgrade->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (level == 1) {
				level++;
				damage += 10;
				upgrade->loadTextures("Money/update_260.png", "Money/update_260.png");
				setTexture("Star/level2.png");
				remove->loadTextures("Money/remove_336.png", "Money/remove_336.png");
			}
			else if (level == 2) {
				level++;
				damage += 10;
				upgrade->loadTextures("Money/update_max.png", "Money/update_max.png");
				setTexture("Star/level3.png");
				remove->loadTextures("Money/remove_560.png", "Money/remove_560.png");
			}
		}
		});

	remove->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			removeFromParent();
			GameManager::getGame()->Money += sellMoney;
		}
		});

}

bool Star::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void Star::onTouchEnded(Touch* touch, Event* event)
{
	//转换坐标系
	Point locationInNode = convertTouchToNodeSpace(touch);

	Size size = getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode))
	{
		if (isUpdateMenuShown)
			hideUpdateMenu();
		else
			showUpdateMenu();
	}
	else {
		hideUpdateMenu();
	}
}