#pragma once
#include"MAP/MAP.h"
#include "Tower/Terrains.h"

class DesertMap :public MAP {
public:
	static DesertMap* createGame();         //������ͼ

	CREATE_FUNC(DesertMap);
private:
	const int towerNum = 9;                 //���Է��õ���������

	void loadPath();                        //װ�ع���·��

	void loadWave();                        //װ��ÿ�����������������

	virtual bool init();                    //��ʼ��

	void addTerrains() override;            //װ�ػ���

};