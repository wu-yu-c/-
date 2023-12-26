#pragma once

#include"cocos2d.h"
#include"Monster.h"
#include"MAP.h"
#include"Tower.h"

class GameManager {
public:

	static GameManager* getGame();

	void GameOver(int levelnum);

	GameManager();

	~GameManager();

	cocos2d::Vector<Monster*> currentMonster;

	cocos2d::Vector<BaseTower*> currentTower;

	int Money;

	int Life;

private:

	bool level[2];

};
