#pragma once
#include "cocos2d.h"
#include<vector>
#include "ui/CocosGUI.h"
#include"Monster/Monster.h"
#include"Carrot/Carrot.h"
#include "Tower/Terrains.h"
enum {
	white, yellow
};

class MAP :public cocos2d::Scene {
public:
	std::vector<Terrains*>terrain;
	CREATE_FUNC(MAP);

protected:

	int wave;               //��ǰ����

	int maxWave;            //�����

	size_t MonsterNum;

	int currentLife;
	int lastLife;

	bool IsStart;          //��Ϸ��ʼ

	bool IsEnd;            //��Ϸ����

	std::vector<std::vector<int>> waveMonster;        //�洢ÿ��������Ϣ������

	CC_SYNTHESIZE(std::vector<cocos2d::Point>, corner, Corner);                          //�洢�ı䷽���λ��

	CC_SYNTHESIZE(std::vector<cocos2d::Point>, path, Path);

	std::vector<cocos2d::Point> terrains;

	void beginAnimation();

	void Count(int i);

	void InitMap();             //��ʼ����ͼ

	virtual void loadPath() { }            //��ȡ����·��

	virtual void loadWave() { }            //��ȡ������Ϣ

	bool InitUI();              //��ʼ��UI���棬�����˵���������ͣ�����Լ����������

	void InitWave();            //��ʼ�����ﲨ����ÿ���Ĺ�������

	void InitEvent();           //��Ӽ�����

	void InitNumber();

	virtual void addWaves(float dt);

	virtual void addMonsters(float dt);

	virtual void addTerrains() { }

	void addMoney(int m, cocos2d::Vec2 pos);

	static void setNumber(int num, cocos2d::Sprite* pos, int color = white);

	void update(float dt);

	void updateMoneyandLife(float dt);

	void GameOver(bool win);

	cocos2d::Vector<Monster*> liveMonster;

	cocos2d::TMXTiledMap* tiledmap;
	cocos2d::TMXObjectGroup* Object;
	cocos2d::TMXObjectGroup* Corner;
	cocos2d::TMXObjectGroup* Point;
	cocos2d::TMXObjectGroup* MyTerrain;

	cocos2d::ui::Button* stopButton;
	cocos2d::ui::Button* menuButton;
	cocos2d::ui::Button* continueButton;

	cocos2d::Sprite* number_1;
	cocos2d::Sprite* number_2;
	cocos2d::Sprite* number_3;
	cocos2d::Sprite* number_4;
	cocos2d::Sprite* number_5;
	cocos2d::Sprite* number_6;

	cocos2d::Sprite* birthPlace;
	Carrot* carrot;
	CC_SYNTHESIZE(cocos2d::Vec2, begin, BirthPlace);
	cocos2d::Layer* chooseMenu;
};