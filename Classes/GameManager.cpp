#include"GameManager.h"
USING_NS_CC;
using namespace cocos2d::ui;

static GameManager* instance;

GameManager::GameManager() {

	level[0] = false;

	level[1] = false;

	Life = 10;

	Money = 0;

}

GameManager* GameManager::getGame() {

	if (instance == NULL)
		instance = new GameManager();

	return instance;

}

void GameManager::GameOver(int levelnum) {

	if (Life > 0)
		level[levelnum] = true;
	else
		level[levelnum] = false;

	currentMonster.clear();

	currentTower.clear();

	Money = 0;

	Life = 10;
}

GameManager::~GameManager() {
	delete instance;
}