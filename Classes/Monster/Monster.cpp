#include"Monster/Monster.h"
#include"Manager/GameManager.h"
#include"MAP/MAP.h"
#include "Manager/SoundManager.h"
USING_NS_CC;
using namespace cocos2d::ui;

Monster::Monster() :
	speed(0),
	Hp(0),
	State(None),
	money(0) {

}

Monster* Monster::createMonster() {

	return Monster::create();
}

/*װ���ƶ�·��*/
void Monster::loadPoint() {
	Vec2 birthPlace = static_cast<MAP*>(Director::getInstance()->getRunningScene())->getBirthPlace();
	const std::vector<Point>& corner = static_cast<MAP*>(Director::getInstance()->getRunningScene())->getCorner();
	const std::vector<Point>& path = static_cast<MAP*>(Director::getInstance()->getRunningScene())->getPath();
	walklong = path[0].getDistance(path[1]);
	for (size_t i = 0, j = 0; i < path.size(); i++) {
		if (abs(path[i].x - corner[j].x) < walklong && abs(path[i].y - corner[j].y) < walklong && j < corner.size()) {
			next.push_back(corner[j]);
			j++;
		}
		else
			next.push_back(path[i]);
	}
	current = birthPlace;
}

/*��ʼ��������Ӧ�¼�*/
void Monster::InitEvent() {

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Monster::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Monster::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

bool Monster::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

/*���մ����¼�*/
void Monster::onTouchEnded(Touch* touch, Event* event)
{
	Point locationInNode = convertTouchToNodeSpace(touch);
	Size size = getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode)) {           //���㵽��ѡ�л�ȡ��ѡ��
		if (chosen)                 
			chosen = false;
		else
			chosen = true;
	}
	else {                                              //δ���㵽���㵽��������ʱȡ��ѡ��
		auto monsters = GameManager::getGame()->currentMonster;        
		Vector<Monster*>::iterator it = monsters.begin();
		for (; it != monsters.end(); it++) {
			auto loc = (*it)->convertTouchToNodeSpace(touch);
			size = (*it)->getContentSize();
			rect = Rect(0, 0, size.width, size.height);
			if (rect.containsPoint(loc)) {
				chosen = false;
			}
		}
	}

}

bool Monster::init() {
	if (!Sprite::init())
		return false;

	IsEffect = false;

	slowspeed = 30;

	IsReverse = false;

	InitEvent();

	return true;
}

/*��ʼ��Ѫ��*/
void Monster::InitHpbar() {

	hpbar_bg = Sprite::create("Monster/hpbar_bg.png");
	hpbar_bg->setPosition(Vec2(width,height));
	addChild(hpbar_bg);

	hpbar = ProgressTimer::create(Sprite::create("Monster/hpbar.png"));
	hpbar->setType(ProgressTimer::Type::BAR);
	hpbar->setMidpoint(Point(0, 0));
	hpbar->setBarChangeRate(Point(1, 0));
	hpbar->setPercentage(100);
	hpbar->setPosition(Vec2(22.5f,5.8f));
	hpbar_bg->addChild(hpbar);

}

/*��������*/
void Monster::birthAnimation() {

	auto animation = Animation::create();

	/*��ȡ������֡*/
	animation->addSpriteFrameWithFile("MONSTER/birthaction1.png");
	animation->addSpriteFrameWithFile("MONSTER/birthaction2.png");

	/*��������Ϊѭ��һ��*/
	animation->setLoops(1);
	/*������֡���ʱ��*/
	animation->setDelayPerUnit(0.1f);

	/*��������*/
	auto action = Animate::create(animation);
	/*�������иö���*/
	runAction(action);

}

/*��������*/
void Monster::killAnimation() {

	stopAllActions();                             //ֹͣ���ж���
	removeAllChildrenWithCleanup(true);           //�������Ѫ���Ƴ�
	GameManager::getGame()->Money += money;       //���ؽ��

	auto killed = Animation::create();

	char namesize[20] = { 0 };
	for (int i = 1; i <= 4; i++) {
		sprintf(namesize, "MONSTER/die_%d.png", i);
		killed->addSpriteFrameWithFile(namesize);
	}

	killed->setLoops(1);
	killed->setDelayPerUnit(0.1f);

	auto smoke = Animate::create(killed);
	
	//�Ȳ�������������Ȼ���Ǯ����󽫹���ӳ������Ƴ�
	runAction(Sequence::create(smoke,
		CallFuncN::create(CC_CALLBACK_0(MAP::addMoney,static_cast<MAP*>(Director::getInstance()->getRunningScene()), money, getPosition())),
		CallFuncN::create(CC_CALLBACK_0(Monster::removeFromParent, this)), NULL));

	SoundManager::PlayMonsterMusic();                                   //���Ź���������Ч
	GameManager::getGame()->currentMonster.eraseObject(this);          //�ӵ�ǰ�������Ƴ�

}

/*��ȡ��һ��λ��*/
Vec2 Monster::nextPoint() {
	auto maxCount = next.size();
	pointCounter++;
	if (pointCounter < maxCount)
		return next[pointCounter];
	else
		pointCounter = maxCount - 1;
	return current;
}

/*��תѪ��*/
void Monster::reverseHpbar() {

	hpbar_bg->runAction(ScaleBy::create(0, -1, 1));

}

/*�ƶ�����һ������*/
void Monster::runNextPoint() {


	tmp = nextPoint();

	if (tmp != current) {
		auto duration = current.getDistance(tmp) / speed;
		
		if (abs(tmp.x - current.x) > walklong && pointCounter > 1) {                      //���ƶ����ս�ʱ�����﷭ת
			runAction(Sequence::create(MoveTo::create(duration, tmp)
				,ScaleBy::create(0.1f, -1, 1)
				,CallFuncN::create(CC_CALLBACK_0(Monster::reverseHpbar,this))
				, CallFuncN::create(CC_CALLBACK_0(Monster::runNextPoint, this))
				, NULL));
			IsReverse = !IsReverse;
		}
		else {
			runAction(Sequence::create(MoveTo::create(duration, tmp)
				, CallFuncN::create(CC_CALLBACK_0(Monster::runNextPoint, this))
				, NULL));
			
		}
		current = tmp;
	}
	else {
		State = Bite;
	}
}

/*�����˺�*/
void Monster::getHurt(int hurt, state effect) {

	Hp -= hurt;

	if (Hp <= 0) {
		State = Death;              //Ѫ��С�ڵ���0ʱ��������״̬
	}
	else {                          //����Ѫ��״̬

		hpbar->setPercentage((Hp / maxHp) * 100);
		State = effect;             //���ù���Ӱ��

	}

}


NormalMonster* NormalMonster::createMonster()
{

	/*�ȴ���һ��ʵ��*/
	auto normal = NormalMonster::create();

	return normal;

}

bool NormalMonster::init() {
	if (!Monster::init())
		return false;

	maxHp=Hp = 80;

	money = 14;

	normalspeed = speed = 70;

	width = 27;
	height = 55;

	scheduleUpdate();

	loadPoint();

	InitAnimation();

	InitHpbar();

	runNextPoint();

	return true;
}

/*�������Ķ���*/
void Monster::attackAnimation() {

	char namesize[30] = { 0 };

	if (!IsEffect) {

		IsEffect = true;

		auto animation = Animation::create();

		auto delay = DelayTime::create(0);

		switch (State) {
		case(Boom):                                                       //��ը��Ч
			animation->addSpriteFrameWithFile("Bottle/Boom1.png");
			animation->addSpriteFrameWithFile("Bottle/Boom2.png");
			animation->setDelayPerUnit(0.05f);
			break; 
		case(Burn):                                                       //ȼ����Ч
			for (int i = 1; i <= 3; i++) {
				sprintf(namesize, "Flower/Burn%d.png", i);
				animation->addSpriteFrameWithFile(namesize);
			}
			animation->setDelayPerUnit(0.1f);
			delay->setDuration(0.5f);
			break;
		case(IceBoom):                                                    //������Ⱥ���˺���Ч
			for (int i = 1; i <= 3; i++) {
				sprintf(namesize, "Star/star%d.png", i);
				animation->addSpriteFrameWithFile(namesize);
			}
		case(Ice):                                                        //������Ч
			speed = slowspeed;
			animation->addSpriteFrameWithFile("Star/Ice.png");
			animation->setDelayPerUnit(0.1f);
			delay->setDuration(2.0f);
			break;
		default:
			break;
		}

		animation->setLoops(1);

		auto effect = Sprite::create();
		addChild(effect);
		effect->setPosition(getContentSize().width / 2, getContentSize().height / 4);

		auto attack = Animate::create(animation);

		/*�Ȳ��ű�����������Ȼ�󽫶����Ƴ�����effctȡ�����ָ���ͨ״̬*/
		effect->runAction(Sequence::create(attack
			, delay
			, CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, effect))
			,CallFuncN::create(CC_CALLBACK_0(Monster::setEffect,this,false))
			,CallFuncN::create(CC_CALLBACK_0(Monster::setnextState,this,None))
			, NULL));

	}

}

/*ˢ�¹����״̬*/
void Monster::update(float dt) {

	/*�Ƿ�ѡ��*/
	if (chosen && getChildByName("target") == NULL) {
		auto target = Sprite::create("MONSTER/chosen.png");
		target->setPosition(getContentSize().width / 2 - 2, height + 5);
		addChild(target);
		target->setName("target");
	}
	else if (!chosen && getChildByName("target") != NULL)
		removeChildByName("target");

	switch (State) {
	case(Bite):                                                          //ҧ���ܲ�
		SoundManager::PlayBiteMusic();                                   //���Ŷ�Ӧ��Ч
		GameManager::getGame()->Life--;                                  //�ܲ�����ֵ��һ
		GameManager::getGame()->currentMonster.eraseObject(this);
		unscheduleUpdate();                                              //ȡ��ˢ��
		removeFromParentAndCleanup(true);
		break;
	case(Death):                                                         //����
		killAnimation();        
		unscheduleUpdate();
		break;
	case(Boom):                                                          //���ֲ�ͬ�ı�������Ч
	case(Burn):
	case(Ice):
	case(IceBoom):
		attackAnimation();
		break;
	case(None):                                                          //��ͨ״̬
		if (speed < normalspeed && !IsEffect)
			speed = normalspeed;
		break;
	default:
		break;
	}

}

/*��ʼ������*/
void NormalMonster::InitAnimation() {

	auto animation = Animation::create();

	/*��ȡ������֡*/
	char namesize[50] = { 0 };
	for (int i = 1; i <= 2; i++) {
		sprintf(namesize, "MONSTER/NormalMonster/action%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	/*��������Ϊ����ѭ��*/
	animation->setLoops(-1);
	/*������֡���ʱ��*/
	animation->setDelayPerUnit(0.1f);

	/*��������*/
	auto action = Animate::create(animation);
	/*�������иö���*/
	runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_0(Monster::birthAnimation, this)), action,NULL));

}

FlyMonster* FlyMonster::createMonster()
{
	auto fly = FlyMonster::create();
	
	fly->InitAnimation();

	return fly;
}

bool FlyMonster::init() {
	if (!Monster::init())
		return false;

	maxHp = Hp = 50;

	money = 50;

	normalspeed = speed = 100;

	width = 40;
	height = 65;

	scheduleUpdate();

	loadPoint();

	InitAnimation();

	InitHpbar();

	runNextPoint();

	return true;
}

void FlyMonster::InitAnimation() {

	auto animation = Animation::create();

	/*��ȡ������֡*/
	char namesize[50] = { 0 };
	for (int i = 1; i <= 2; i++) {
		sprintf(namesize, "MONSTER/FlyMonster/action%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	/*��������Ϊ����ѭ��*/
	animation->setLoops(-1);
	/*������֡���ʱ��*/
	animation->setDelayPerUnit(0.2f);

	/*��������*/
	auto action = Animate::create(animation);
	/*�������иö���*/
	runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_0(Monster::birthAnimation, this)), action,NULL));

}

BigMonster* BigMonster::createMonster()
{
	auto big = BigMonster::create();

	big->InitAnimation();

	return big;
}


bool BigMonster::init() {
	if (!Monster::init())
		return false;

	maxHp = Hp = 150;

	money = 75;

	normalspeed = speed = 50;

	width = 40;
	height = 85;

	scheduleUpdate();

	loadPoint();

	InitAnimation();

	InitHpbar();

	runNextPoint();

	return true;
}

void BigMonster::InitAnimation() {

	auto animation = Animation::create();

	/*��ȡ������֡*/
	char namesize[50] = { 0 };
	for (int i = 1; i <= 2; i++) {
		sprintf(namesize, "MONSTER/BigMonster/action%d.png", i);
		animation->addSpriteFrameWithFile(namesize);
	}

	/*��������Ϊ����ѭ��*/
	animation->setLoops(-1);
	/*������֡���ʱ��*/
	animation->setDelayPerUnit(0.1f);

	/*��������*/
	auto action = Animate::create(animation);
	/*�������иö���*/
	runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_0(Monster::birthAnimation, this)), action,NULL));
	
}

