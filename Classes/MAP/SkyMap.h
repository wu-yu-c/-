#pragma once
#include"Tower/Terrains.h"
#include"MAP/MAP.h"
const int towerNum = 8;
class SkyMap :public MAP {
public:
	static SkyMap* createGame();            //������ͼ

	CREATE_FUNC(SkyMap);
private:
	 
	void loadPath();                       //װ�ع����ƶ�·��

	void loadWave();                       //װ��ÿ��������Ϣ

	virtual bool init();

	void addTerrains()override;           //װ�ػ���
};
