#pragma once
#include "enemy.h"
#include "boxEnemy.h"

class enemyManager
{
private:
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	vector<enemy*> getEnemy() { return _vEnemy; }

	enemyManager() {}
	~enemyManager() {}
};

