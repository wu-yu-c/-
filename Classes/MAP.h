#pragma once
#include "cocos2d.h"
#include<vector>
#include "ui/CocosGUI.h"
#include"Monster.h"
#include"Carrot.h"

class MAP :public cocos2d::Scene {
public:

	CREATE_FUNC(MAP);

	void BiteCarrot();

protected:
	 
	int wave;               //当前波数

	int maxWave;            //最大波数

	CC_SYNTHESIZE(int, currentLife, CurrentLife);        //当前生命

	size_t MonsterNum;

	int money;              //钱数

	bool IsStart;          //游戏开始

	bool IsEnd;            //游戏结束

	std::vector<std::vector<int>> waveMonster;        //存储每波怪物信息的容器

	CC_SYNTHESIZE(std::vector<cocos2d::Point>,corner,Corner);                          //存储改变方向的位置

	CC_SYNTHESIZE(std::vector<cocos2d::Point>, path, Path);

	std::vector<cocos2d::Point> terrains;

	cocos2d::Vector<Monster*> currentMonster;                      //存储当前波怪物

	void beginAnimation();

	void Count(int i);

	void InitMap();             //初始化地图

	virtual void loadPath() { }            //读取怪物路径

	virtual void loadWave() { }            //读取怪物信息

	bool InitUI();              //初始化UI界面，包括菜单按键和暂停按键以及怪物出生点

	void InitWave();            //初始化怪物波数和每波的怪物类型

	void InitEvent();           //添加监听器

	virtual void addWaves(float dt);

	virtual void addMonsters(float dt);

	virtual void addTerrains() { }

	void update(float dt);

	void updateMoneyandLife();

	void Victory();

	cocos2d::Vector<Monster*> liveMonster;

	cocos2d::TMXTiledMap* tiledmap;
	cocos2d::TMXObjectGroup* Object;
	cocos2d::TMXObjectGroup* Corner;
	cocos2d::TMXObjectGroup* Point;
	cocos2d::TMXObjectGroup* MyTerrain;
	cocos2d::ui::Button* stopButton;
	cocos2d::ui::Button* menuButton;
	cocos2d::Sprite* birthPlace;
	CC_SYNTHESIZE(cocos2d::Vec2, begin, BirthPlace);
	Carrot* carrot;
	cocos2d::Layer* chooseMenu;
	cocos2d::ui::Button* continueButton;
};

class ChooseMenu :public cocos2d::Layer {
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();

	CREATE_FUNC(ChooseMenu);
private:
	bool InitUI();

	void InitEvent();

	cocos2d::ui::Button* restartButton;
	//cocos2d::ui::Button* continueButton;
	cocos2d::ui::Button* returnButton;
};