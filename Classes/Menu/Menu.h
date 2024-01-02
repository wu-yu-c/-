#pragma once
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"MAP/DesertMap.h"
#include"MAP/SkyMap.h"

/*��Ϸ�ڲ˵�*/
class ChooseMenu :public cocos2d::Layer {
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();

	CREATE_FUNC(ChooseMenu);
private:
	bool InitUI();

	void InitEvent();

	cocos2d::ui::Button* restartButton;             //���¿�ʼ��ť
	cocos2d::ui::Button* returnButton;              //����ѡ�ؽ��水ť
};

/*����˵�*/
class OverMenu :public cocos2d::Layer {
public:
	static cocos2d::Layer* createMenu(bool IsWin,int max,int current);

	CREATE_FUNC(OverMenu);

private:
	bool Win;                                 //�Ƿ�ʤ��

	int maxWave;                              //�����

	int wave;                                 //��ǰ����

	cocos2d::ui::Button* returnButton;        //����ѡ�ؽ��水ť
	cocos2d::ui::Button* continueButton;      //������Ϸ��ť

	bool InitMenu();

	void InitUI();

	void Result();                           //������Ϸ���

	void InitEvent();

};