#pragma once

#include"MAP.h"

class DesertMap :public MAP {
public:
	static DesertMap* createGame();

	void loadPath();

	virtual bool init();

	CREATE_FUNC(DesertMap);

};