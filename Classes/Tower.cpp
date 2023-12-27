#include "Tower.h"
#include "cocos2d.h"
#include "Terrains.h"
#include "MAP.h"
#include <vector>
#include"GameManager.h"
#include "Bullet.h"
#include<math.h>
using namespace cocos2d::ui;

char basename[3][30] = {
	"Bottle/Bottle_3.png",
};

bool BaseTower::init() {

	if (!Sprite::init())
		return false;

	chosenEnemy = NULL;

	return true;
}

void BaseTower::buildAnimation(char* name,int i) {

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

void BaseTower::InitBase(int i) {

	auto base = Sprite::create(basename[i]);
	base->setPosition(40, 40);
	addChild(base,-1);

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

	if (distance < attackRange->getContentSize().width/2 || distance < attackRange->getContentSize().height/2)
		return true;
	else
		return false;

}

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

		bullet->runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_0(BottleBullet::shoot, bullet))
			, MoveTo::create(0.2f, dst)
			, CallFuncN::create(CC_CALLBACK_0(BottleBullet::removeFromParent, bullet))
			, NULL));

	}
}

bool Bottle::init() {

	if (!Sprite::init())
		return false;

	buildAnimation("Bottle/Bottle11.png", 0);

	initLevel();

	initEvent();

	scheduleUpdate();

	schedule(schedule_selector(Bottle::attack), rate);

	return true;

}

void Bottle::initLevel()
{

	//添加升级按钮
	upgrade = Button::create("Money/update_180.png", "Money/update_180.png", "");
	upgrade->setPosition(Vec2(40,110));
	upgrade->setPressedActionEnabled(true);
	upgrade->setVisible(false);
	this->addChild(upgrade, 3);

	//添加拆除按钮
	remove = Button::create("Money/remove_80.png", "Money/remove_80.png", "");
	remove->setPosition(Vec2(40,-30));
	remove->setPressedActionEnabled(true);
	remove->setVisible(false);
	this->addChild(remove, 3);

	//初始化数据
	level = 1;
	rate = 1.0f;
	scope = 0.8f;
	attackRange = cocos2d::Sprite::create("GamePlay/range.png");
	attackRange->setPosition(40,40);
	attackRange->setScale(scope);
	addChild(attackRange);
	attackRange->setVisible(false);
	isUpdateMenuShown = false;
}

//添加事件监听器
void Bottle::initEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Bottle::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Bottle::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	upgrade->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (level == 1) {
				level++;
				damage += 10;
				upgrade->loadTextures("Money/update_220.png", "Money/update_220.png");
				setTexture("Bottle/Bottle21.png");
				remove->loadTextures("Money/remove_224.png", "Money/remove_224.png");
			}
			else if (level == 2) {
				level++;
				damage += 10;
				upgrade->loadTextures("Money/update_max.png", "Money/update_max.png");
				setTexture("Bottle/Bottle31.png");
				remove->loadTextures("Money/remove_432.png", "Money/remove_432.png");
			}
		}
		});

	remove->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			/*此处应将基座设为可触摸*/
			removeFromParent();
			GameManager::getGame()->Money += sellMoney;

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
		return -degrees-180;
	else
		return -degrees - 180;

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

BaseTower* Flower::createFlowerTower(int tag)
{
	auto newflower = new Flower();

	if (newflower && newflower->myInit(tag))
	{
		newflower->autorelease();
		return newflower;
	}
	CC_SAFE_DELETE(newflower);
	return NULL;
}

bool Flower::myInit(int tag)
{
	if (!Sprite::init())
		return false;

	initLevel(tag);

	initEvent();

	return true;
}

void Flower::initLevel(int tag)
{
	auto nowScene = Director::getInstance()->getRunningScene();
	auto nowTerrain = nowScene->getChildByTag(tag);

	flower = Sprite::create("Flower/merge1.png");
	flower->setPosition(nowTerrain->getPosition());
	this->addChild(flower, 2);

	//添加升级按钮
	upgrade = Button::create("Money/update_220.png", "Money/update_220.png", "");
	upgrade->setPosition(Vec2(nowTerrain->getPositionX(), nowTerrain->getPositionY() + 60));
	upgrade->setPressedActionEnabled(true);
	upgrade->setVisible(false);
	this->addChild(upgrade, 3);

	//添加拆除按钮
	remove = Button::create("Money/remove_144.png", "Money/remove_144.png", "");
	remove->setPosition(Vec2(nowTerrain->getPositionX(), nowTerrain->getPositionY() - 60));
	remove->setPressedActionEnabled(true);
	remove->setVisible(false);
	this->addChild(remove, 3);

	//初始化数据
	level = 1;
	damage = 10;
	isUpdateMenuShown = false;
}

void Flower::showAttackRange()
{
	// 创建并显示攻击范围的圆形精灵
	attackRange = cocos2d::Sprite::create("GamePlay/range.png");
	attackRange->setPosition(flower->getPosition());
	attackRange->setScale(1.5f);
	this->addChild(attackRange);
}

//显示升级菜单
void Flower::showUpdateMenu()
{
	if (isUpdateMenuShown == false) {
		isUpdateMenuShown = true;
		showAttackRange();
		upgrade->setVisible(true);
		remove->setVisible(true);
	}
}

void Flower::hideAttackRange()
{
	attackRange->removeFromParent();
}

//隐藏升级菜单
void Flower::hideUpdateMenu()
{
	if (isUpdateMenuShown == true) {
		isUpdateMenuShown = false;
		hideAttackRange();
		upgrade->setVisible(false);
		remove->setVisible(false);
	}
}

//添加事件监听器
void Flower::initEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Flower::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Flower::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, flower);

	upgrade->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (level == 1) {
				level++;
				damage += 10;
				upgrade->loadTextures("Money/update_260.png", "Money/update_260.png");
				flower->setTexture("Flower/merge2.png");
				remove->loadTextures("Money/remove_336.png", "Money/remove_336.png");
			}
			else if (level == 2) {
				level++;
				damage += 10;
				upgrade->loadTextures("Money/update_max.png", "Money/update_max.png");
				flower->setTexture("Flower/merge3.png");
				remove->loadTextures("Money/remove_560.png", "Money/remove_560.png");
			}
		}
		});

	remove->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto nowScene = Director::getInstance()->getRunningScene();
			auto nowTower = nowScene->getChildByTag(getTag());
			auto newTerrain = Terrains::createTerrain();
			newTerrain->setTag(nowTower->getTag());
			newTerrain->setPosition(flower->getPosition());
			nowTower->removeFromParent();
			nowScene->addChild(newTerrain, 0);
			if (level == 1) {

			}
			else if (level == 2) {

			}
			else if (level == 3) {

			}
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
	Point locationInNode = flower->convertTouchToNodeSpace(touch);

	Size size = flower->getContentSize();
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

BaseTower* Star::createStarTower(int tag)
{
	auto newstar = new Star();

	if (newstar && newstar->myInit(tag))
	{
		newstar->autorelease();
		return newstar;
	}
	CC_SAFE_DELETE(newstar);
	return NULL;
}

bool Star::myInit(int tag)
{
	if (!Sprite::init())
		return false;

	initLevel(tag);

	initEvent();

	return true;
}

void Star::initLevel(int tag)
{
	auto nowScene = Director::getInstance()->getRunningScene();
	auto nowTerrain = nowScene->getChildByTag(tag);

	//添加底座
	auto dizuo = Sprite::create("Star/level3_base.png");
	dizuo->setPosition(nowTerrain->getPosition());
	this->addChild(dizuo, 1);

	star = Sprite::create("Star/level1.png");
	star->setPosition(nowTerrain->getPosition());
	this->addChild(star, 2);

	//添加升级按钮
	upgrade = Button::create("Money/update_220.png", "Money/update_220.png", "");
	upgrade->setPosition(Vec2(nowTerrain->getPositionX(), nowTerrain->getPositionY() + 60));
	upgrade->setPressedActionEnabled(true);
	upgrade->setVisible(false);
	this->addChild(upgrade, 3);

	//添加拆除按钮
	remove = Button::create("Money/remove_144.png", "Money/remove_144.png", "");
	remove->setPosition(Vec2(nowTerrain->getPositionX(), nowTerrain->getPositionY() - 60));
	remove->setPressedActionEnabled(true);
	remove->setVisible(false);
	this->addChild(remove, 3);

	//初始化数据
	level = 1;
	damage = 10;
	isUpdateMenuShown = false;
}

void Star::showAttackRange()
{
	// 创建并显示攻击范围的圆形精灵
	attackRange = cocos2d::Sprite::create("GamePlay/range.png");
	attackRange->setPosition(star->getPosition());
	attackRange->setScale(2.0f);
	this->addChild(attackRange);
}

//显示升级菜单
void Star::showUpdateMenu()
{
	if (isUpdateMenuShown == false) {
		isUpdateMenuShown = true;
		showAttackRange();
		upgrade->setVisible(true);
		remove->setVisible(true);
	}
}

void Star::hideAttackRange()
{
	attackRange->removeFromParent();
}

//隐藏升级菜单
void Star::hideUpdateMenu()
{
	if (isUpdateMenuShown == true) {
		isUpdateMenuShown = false;
		hideAttackRange();
		upgrade->setVisible(false);
		remove->setVisible(false);
	}
}

//添加事件监听器
void Star::initEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Star::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Star::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, star);

	upgrade->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (level == 1) {
				level++;
				damage += 10;
				upgrade->loadTextures("Money/update_260.png", "Money/update_260.png");
				star->setTexture("Star/level2.png");
				remove->loadTextures("Money/remove_336.png", "Money/remove_336.png");
			}
			else if (level == 2) {
				level++;
				damage += 10;
				upgrade->loadTextures("Money/update_max.png", "Money/update_max.png");
				star->setTexture("Star/level3.png");
				remove->loadTextures("Money/remove_560.png", "Money/remove_560.png");
			}
		}
		});

	remove->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto nowScene = Director::getInstance()->getRunningScene();
			auto nowTower = nowScene->getChildByTag(getTag());
			auto newTerrain = Terrains::createTerrain();
			newTerrain->setTag(nowTower->getTag());
			newTerrain->setPosition(star->getPosition());
			nowTower->removeFromParent();
			nowScene->addChild(newTerrain, 0);
			if (level == 1) {

			}
			else if (level == 2) {

			}
			else if (level == 3) {

			}
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
	Point locationInNode = star->convertTouchToNodeSpace(touch);

	Size size = star->getContentSize();
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

//Monster* BaseTower::getCloseMonster()
//{
//	Monster* closeMonster = NULL;
//	double maxDistance = 99999;
//	auto nowMonster = static_cast<MAP*>(Director::getInstance()->getRunningScene())->currentMonster;
//	for (size_t i = 0; i < nowMonster.size(); i++) {
//		auto monster = nowMonster.at(i);
//		Vec2 towerPosition = this->getPosition();
//		Vec2 monsterPosition = monster->getPosition();
//		double distance = sqrt(pow(towerPosition.x - monsterPosition.x, 2) + pow(towerPosition.y - monsterPosition.y, 2));
//		if (distance < maxDistance) {
//			closeMonster = monster;
//			maxDistance = distance;
//		}
//	}
//	if (maxDistance < this->range)
//		return closeMonster;
//	return NULL;
//}

//void Bottle::Spin(float dt)
//{
//    this->targetMonster = this->getCloseMonster();
//
//    if (this->targetMonster != NULL) 
//    {
//        Point shootVector = this->targetMonster->getPosition() - this->getPosition();
//        float shootAngle = ccpToAngle(shootVector);//得到弧度值
//        float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);//将弧度转化为角度
//
//        float rotateSpeed = 0.5 / M_PI;
//        float rotateDuration = fabs(shootAngle * rotateSpeed);
//
//        bottle->runAction(Sequence::create(RotateTo::create(rotateDuration,cocosAngle),NULL));
//
//		bottle->runAction(Sequence::create(RotateTo::create(rotateDuration, cocosAngle), CallFunc::create(this, callfunc_selector(Bottle::shoot)), NULL));
//    }
//}
//
//void Bottle::shoot()
//{
//	if (this->targetMonster != NULL) {
//		bullet = BottleBullet::create();
//		bullet->setPosition(bottle->getPosition());
//		Director::getInstance()->getRunningScene()->addChild(bullet, 1);
//
//
//	}
//}