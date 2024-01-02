#pragma once

#include"cocos2d.h"
#include"Monster/Monster.h"
#include"MAP/MAP.h"
#include"Tower/Tower.h"

class GameManager {
public:

	static GameManager* getGame();                 //��ȡ��ǰ��Ϸ����Ϣ

	void init();

	void setResult();                             //���ñ�����Ϸ�Ľ��

	int getResult(int level) const;                     //��ö�Ӧ�ؿ��Ľ��

	GameManager();

	~GameManager();

	cocos2d::Vector<Monster*> currentMonster;            //��ǰ��Ϸ���Ĺ���

	int Money;                                    //��ǰ��Ϸ��Ǯ��

	int Life;                                     //��ǰ��Ϸ�ܲ�������ֵ

	int currentLevel;                             //��ǰ�ؿ���

	int maxLevel;                                 //���ؿ���

public:

	int level[2];                                 //��¼�ؿ��Ƿ�ʤ��

};
