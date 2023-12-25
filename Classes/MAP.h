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
	 
	int wave;               //��ǰ����

	int maxWave;            //�����

	CC_SYNTHESIZE(int, currentLife, CurrentLife);        //��ǰ����

	size_t MonsterNum;

	int money;              //Ǯ��

	bool IsStart;          //��Ϸ��ʼ

	bool IsEnd;            //��Ϸ����

	std::vector<std::vector<int>> waveMonster;        //�洢ÿ��������Ϣ������

	CC_SYNTHESIZE(std::vector<cocos2d::Point>,corner,Corner);                          //�洢�ı䷽���λ��

	CC_SYNTHESIZE(std::vector<cocos2d::Point>, path, Path);

	std::vector<cocos2d::Point> terrains;

	cocos2d::Vector<Monster*> currentMonster;                      //�洢��ǰ������

	void beginAnimation();

	void Count(int i);

	void InitMap();             //��ʼ����ͼ

	virtual void loadPath() { }            //��ȡ����·��

	virtual void loadWave() { }            //��ȡ������Ϣ

	bool InitUI();              //��ʼ��UI���棬�����˵���������ͣ�����Լ����������

	void InitWave();            //��ʼ�����ﲨ����ÿ���Ĺ�������

	void InitEvent();           //��Ӽ�����

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