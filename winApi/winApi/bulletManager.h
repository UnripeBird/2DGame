#pragma once
#include "bullet.h"

class bulletManager
{
private:
	vector<bullet*> _vBullet;
	vector<bullet*>::iterator _viBullet;
	vector<bullet*> _vEnemyBullet;
	vector<bullet*>::iterator _viEnemyBullet;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void bulletFire(BULLETDISCERN discernNum, POINT pos, bool leftRight);
	void enemyFire(BULLETDISCERN discernNum, POINT pos, float angle = (PI / 180) * 180);
	vector<bullet*> getBullet() { return _vBullet; }
	vector<bullet*> getEnemyBullet() { return _vEnemyBullet; }
	bulletManager() {}
	~bulletManager() {}
};

