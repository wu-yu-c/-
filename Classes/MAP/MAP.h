#pragma once
#include "cocos2d.h"
#include<vector>
#include "ui/CocosGUI.h"
#include"Monster/Monster.h"
#include"Carrot/Carrot.h"
#include "Tower/Terrains.h"

/*�������ֵ���ɫ*/
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

	size_t MonsterNum;      //��ǰ��������

	int currentLife;        //��ǰ�ܲ�����ֵ
	int lastLife;           //�ܲ��仯ǰ������ֵ

	bool IsEnd;             //��¼ÿ���Ƿ����

	std::vector<std::vector<int>> waveMonster;                          //�洢ÿ���������Ϣ

	CC_SYNTHESIZE(std::vector<cocos2d::Point>, corner, Corner);         //�洢�ı䷽���λ��

	CC_SYNTHESIZE(std::vector<cocos2d::Point>, path, Path);             //�洢�����ƶ�·��

	std::vector<cocos2d::Point> terrains;                               //�洢����λ��

	void beginAnimation();       //��ʼ����
	 
	void Count(int i);          //����ʱ����

	void InitMap();             //��ʼ����ͼ

	virtual void loadPath() { }            //��ȡ����·��

	virtual void loadWave() { }            //��ȡ������Ϣ

	bool InitUI();              //��ʼ��UI���棬�����˵���������ͣ�����Լ����������

	void InitWave();            //��ʼ�����ﲨ����ÿ���Ĺ�������

	void InitEvent();           //��Ӽ�����

	void InitNumber();          //��ʼ������

	virtual void addWaves(float dt);              //����һ������

	virtual void addMonsters(float dt);           //����ÿ������

	virtual void addTerrains() { }

	void addMoney(int m, cocos2d::Vec2 pos);      //���������ڶ�Ӧλ����ʾ����Ǯ��

	static void setNumber(int num, cocos2d::Sprite* pos, int color = white);           //�����ڶ�Ӧλ����ʾ������

	void update(float dt);                        //ˢ��Ǯ�����ܲ�����ֵ

	void GameOver(bool win);                      //��Ϸ��������ݽ�����ò�ͬ��OverMenu

	cocos2d::TMXTiledMap* tiledmap;               //��Ƭ��ͼ
	cocos2d::TMXObjectGroup* Object;              //����λ�á����������λ�á��ܲ�λ�á���ťλ��
	cocos2d::TMXObjectGroup* Corner;              //·���սǵ�λ��
	cocos2d::TMXObjectGroup* Point;               //·��ÿ���λ��
	cocos2d::TMXObjectGroup* MyTerrain;           //������λ��

	cocos2d::ui::Button* stopButton;
	cocos2d::ui::Button* menuButton;
	cocos2d::ui::Button* continueButton;

	cocos2d::Sprite* number_1;                    //��Ǯǧλ
	cocos2d::Sprite* number_2;                    //��Ǯ��λ
	cocos2d::Sprite* number_3;                    //��Ǯʮλ
	cocos2d::Sprite* number_4;                    //��Ǯ��λ
	cocos2d::Sprite* number_5;                    //��ǰ����ʮλ
	cocos2d::Sprite* number_6;                    //��ǰ������λ

	cocos2d::Sprite* birthPlace;                  //���������
	Carrot* carrot;                               //�ܲ�

	CC_SYNTHESIZE(cocos2d::Vec2, begin, BirthPlace);    //������λ��
	cocos2d::Layer* chooseMenu;                         //�˵�����
};