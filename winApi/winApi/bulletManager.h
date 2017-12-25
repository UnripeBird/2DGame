#pragma once
#include "bullet.h"

class bulletManager
{
private:
	vector<bullet*> _vBullet;
	vector<bullet*>::iterator _viBullet;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void bulletFire(BULLETDISCERN discernNum, POINT pos, bool leftRight);
	vector<bullet*> getBullet() { return _vBullet; }
	bulletManager() {}
	~bulletManager() {}
};

