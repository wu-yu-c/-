#include"DesertMap.h"
USING_NS_CC;
using namespace cocos2d::ui;

void DesertMap::loadPath() {

	float x, y;

	Corner =tiledmap->getObjectGroup("Corner");

	/*创建几段移动动作，corner坐标从瓦片地图获取*/
	const Vec2 begin = birthPlace->getPosition();

	ValueMap corner1 = Corner->getObject("corner1");
	x = corner1["x"].asFloat();
	y = corner1["y"].asFloat();
	auto move1 = MoveTo::create(3, Vec2(x, y));

	ValueMap corner2 = Corner->getObject("corner2");
	x = corner2["x"].asFloat();
	y = corner2["y"].asFloat();
	auto move2 = MoveTo::create(3, Vec2(x, y));

	const Vec2 end = Carrot->getPosition();
	auto move3 = MoveTo::create(3, end);

	/*创建动作序列*/
	movepath = Sequence::create(move1, move2, move3, NULL);

}

DesertMap* DesertMap::createGame() {

	auto desertmap = DesertMap::create();

	return desertmap;

}

bool DesertMap::init() {
	if (!Scene::init())
		return false;

	tiledmap = TMXTiledMap::create("MAP/DESERT/TileMap2.tmx");

	addChild(tiledmap, -1);
	if (tiledmap == nullptr)
		return false;

	Object = tiledmap->getObjectGroup("Object");

	InitUI();

	InitEvent();

	return true;
}