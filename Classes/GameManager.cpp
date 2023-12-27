#include"GameManager.h"
USING_NS_CC;
using namespace cocos2d::ui;

static GameManager* instance;

GameManager::GameManager() {

	level[0] = false;

	level[1] = false;

}

void GameManager::init() {

	currentMonster.clear();

	currentTower.clear();

	Money = 0;

	Life = 10;

}

GameManager* GameManager::getGame() {

	if (instance == NULL)
		instance = new GameManager();

	return instance;

}

void GameManager::setResult() {

	if (Life > 0)
		level[currentLevel-1] = true;
	else
		level[currentLevel] = false;

}

GameManager::~GameManager() {
	delete instance;
}