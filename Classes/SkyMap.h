#pragma once

#include"MAP.h"

class SkyMap :public MAP {
public:
	static SkyMap* createGame();

	CREATE_FUNC(SkyMap);
private:

	void loadPath();

	void loadWave();

	virtual bool init();

};
