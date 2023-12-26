#pragma once

#include"MAP.h"

class DesertMap :public MAP {
public:
	static DesertMap* createGame();

	CREATE_FUNC(DesertMap);
private:
	void loadPath();

	void loadWave();

	virtual bool init();

	void addTerrains() override;

};