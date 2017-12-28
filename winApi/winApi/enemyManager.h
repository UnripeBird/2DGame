#pragma once
#include "enemy.h"
#include "fieldObject.h"
#include "bulletManager.h"
#include "bullet.h"
#include "boxEnemy.h"
#include "waddle.h"
#include "frog.h"
#include "brontoburt.h"
#include "burning.h"
#include "spark.h"
#include "chilly.h"
#include "woodboss.h"

class enemyManager
{
private:
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;

public:
	HRESULT init(void);
	void release(void);
	void update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, int curMapNum, bulletManager* BulletManager);
	void mapsetting(int i);
	void mapmonster1();
	void mapmonster2();
	void mapmonster3();
	vector<enemy*> getEnemy() { return _vEnemy; }

	enemyManager() {}
	~enemyManager() {}
};

