#pragma once
#include "enemy.h"
#include "boxEnemy.h"
#include "waddle.h"
#include "frog.h"
#include "brontoburt.h"
class enemyManager
{
private:
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;

public:
	HRESULT init(void);
	void release(void);
	void update(image* pixelimage, POINT playerPoint);

	vector<enemy*> getEnemy() { return _vEnemy; }

	enemyManager() {}
	~enemyManager() {}
};

