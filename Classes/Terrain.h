<<<<<<< Updated upstream
#include "cocos2d.h"

USING_NS_CC;

class Terrains : public Sprite {

public:
	virtual bool init();
	static Terrains* createTerrain();
	void showUpdateMenu();
	void hideUpdateMenu();
	Sprite* terrain;
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	bool isUpdateMenuShown;
=======
#include "cocos2d.h"

USING_NS_CC;

class Terrains : public Sprite {

public:
	virtual bool init();
	static Terrains* createTerrain();
	void showUpdateMenu();
	void hideUpdateMenu();
	Sprite* terrain;
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	bool isUpdateMenuShown;
>>>>>>> Stashed changes
};