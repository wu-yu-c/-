#pragma once

#include"cocos2d.h"
#include"Monster.h"
#include"MAP.h"
#include"Tower.h"

class GameManager {
public:

	static GameManager* getGame();

	void init();

	void setResult();

	bool getResult(int level);

	GameManager();

	~GameManager();

	cocos2d::Vector<Monster*> currentMonster;

	cocos2d::Vector<BaseTower*> currentTower;

	int Money;

	int Life;

	int currentLevel;

	int maxLevel;

private:

	bool level[2];       //��¼�ؿ��Ƿ�ʤ��


};
