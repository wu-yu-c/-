#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class Carrot :public cocos2d::Sprite {
public:
	CREATE_FUNC(Carrot);

	void setLife(int n);          //�����ܲ�����ֵ�ı��ܲ���̬��nΪ��ǰ����ֵ

	void BiteCarrot(int n);       //�ܲ���ҧ��Ķ���

private:
	int Life;                     //�ܲ�������
	int count;                    //��������
	cocos2d::Sprite* life;        //������
	cocos2d::ui::Button* updateButton;    //������ť
	bool isUpdateMenuShown;               //�Ƿ����������˵�
	virtual bool init();
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void updateCarrot();                  //�����ܲ�
	void shakeAnimation(float dt);        //�ܲ��Ķ�������
	void showUpdateMenu();                //��ʾ�����˵�
	void initEvent();
};