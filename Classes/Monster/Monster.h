#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include<vector>

/*����Ķ���״̬*/
typedef enum {
	None,Death,Bite,Burn,Ice,Boom,IceBoom
} state;

/*���������*/
typedef enum {
	normal, fly, big
} monsterName;

/*�������*/
class Monster:public cocos2d::Sprite {
public:
	CREATE_FUNC(Monster);
	
	Monster* createMonster();

	Monster();

	virtual bool init() override;

	void loadPoint();

	void update(float dt) override;

	void getHurt(int hurt, state effect = None);          //�����˺�

	CC_SYNTHESIZE(bool, chosen, Chosen);                  //�Ƿ�ѡ��

	bool IsReverse;                                       //�Ƿ�ת��

protected:

	CC_SYNTHESIZE(float, maxHp, Maxhp);                  //���Ѫ��
	CC_SYNTHESIZE(float, Hp, Hp);                        //��ǰѪ��
	CC_SYNTHESIZE(int,speed,speed);                      //��ǰ�ƶ��ٶ�
	int normalspeed;                                     //�����ƶ��ٶ�
	int slowspeed;                                       //���ٺ��ƶ��ٶ�
	CC_SYNTHESIZE(int, money, Money);                    //���ؽ����
	float walklong;                                      //һ���ƶ��ľ���
	float width;                                         //�����ȣ���������Ѫ��λ��
	int height;                                          //����߶ȣ���������Ѫ��λ��
	size_t pointCounter;                                 //��¼���ﵱǰ�ߵ���λ��
	CC_SYNTHESIZE(cocos2d::ProgressTimer*, hpbar, Hpbar);     //Ѫ��
	cocos2d::Sprite* hpbar_bg;                                //Ѫ������
	std::vector<cocos2d::Point> next;                         //��һ���ƶ�����λ��
	cocos2d::Vec2 nextPoint();                                //��ȡ��һ��λ��
	cocos2d::Vec2 tmp;                                        //�ݴ���һ��λ��
	CC_SYNTHESIZE(cocos2d::Vec2,current,Current);             //��ǰλ��
	CC_SYNTHESIZE(state, State, nextState);                   //��Ҫ�ı��״̬
	CC_SYNTHESIZE(bool, IsEffect, Effect);                    //�Ƿ��ܵ�����Ӱ��
	 
	void InitHpbar();                       //��ʼ��Ѫ��

	void runNextPoint();                    //�ƶ�����һ��λ��

	void birthAnimation();                  //��������

	void killAnimation();                   //��������

	void attackAnimation();                 //�������Ķ���

	void reverseHpbar();                    //��תѪ��

	void InitEvent();                 

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event); 

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

class NormalMonster :public Monster {
public:
	static NormalMonster* createMonster();

	virtual bool init();

	void InitAnimation();

	CREATE_FUNC(NormalMonster);
};

class FlyMonster :public Monster {
public:
	static FlyMonster* createMonster();

	virtual bool init();

	void InitAnimation();

	CREATE_FUNC(FlyMonster);
};

class BigMonster :public Monster {
public:
	static BigMonster* createMonster();

	virtual bool init();

	void InitAnimation();

	CREATE_FUNC(BigMonster);
};
