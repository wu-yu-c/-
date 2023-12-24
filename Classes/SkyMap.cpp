#include"SkyMap.h"
#include<vector>
#include "Terrains.h"
USING_NS_CC;
using namespace cocos2d::ui;

void SkyMap::loadPath() {

	float x, y;

	char namesize[10] = { 0 };
	for (int i = 1; i <= 41; i++) {
		sprintf(namesize, "p%d", i);
		ValueMap point = Point->getObject(namesize);
		x = point["x"].asFloat();
		y = point["y"].asFloat();
		path.push_back(Vec2(x, y));
	}
	for (int i = 1; i <= 4; i++) {
		sprintf(namesize, "corner%d", i);
		ValueMap point = Corner->getObject(namesize);
		x = point["x"].asFloat();
		y = point["y"].asFloat();
		corner.push_back(Vec2(x, y));
	}
	ValueMap carrotloc = Object->getObject("carrot");
	x = carrotloc["x"].asFloat();
	y = carrotloc["y"].asFloat();
	corner.push_back(Vec2(x, y));

}

void SkyMap::addTerrains()
{
	float x, y;
	char namesize[10] = { 0 };
	for (int i = 1; i <= towerNum; i++) {
		sprintf(namesize, "tower%d", i);
		ValueMap point = MyTerrain->getObject(namesize);
		x = point["x"].asFloat();
		y = point["y"].asFloat();
		terrains.push_back(Vec2(x, y));
	}
	Terrains* terrain[towerNum];
	for (int i = 0; i < towerNum; i++) {
		terrain[i] = Terrains::createTerrain();
		terrain[i]->setPosition(terrains.at(i));
		terrain[i]->setTag(i + 1);
		addChild(terrain[i], 0);
	}
}

void SkyMap::loadWave() {
	std::vector<std::vector<int>> skywave = {
		{normal,normal,normal},
		{fly,fly,fly},
		{big,big,big}
	};

	for (int i = 0; i < skywave.size(); i++)
		waveMonster.push_back(skywave.at(i));

	maxWave = skywave.size();
}

SkyMap* SkyMap::createGame() {

	auto skymap = SkyMap::create();
	return skymap;

}

bool SkyMap::init() {
	if (!Scene::init())
		return false;

	tiledmap = TMXTiledMap::create("MAP/SKY/TileMap1.tmx");
	Corner = tiledmap->getObjectGroup("Corner");
	Object = tiledmap->getObjectGroup("Object");
	Point = tiledmap->getObjectGroup("Point");
	MyTerrain = tiledmap->getObjectGroup("Tower");

	addChild(tiledmap, -1);
	if (tiledmap == nullptr)
		return false;

	loadWave();

	loadPath();

	addTerrains();

	InitMap();

	return true;

}
