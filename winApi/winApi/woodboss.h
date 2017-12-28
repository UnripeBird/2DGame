#pragma once
#include "enemy.h"

class woodboss :
	public enemy
{
private:

	float _moveSpeed;
	BOOL _whisle;
	BOOL _missile;
	POINT _rezen;
	int _hp;
public:
	HRESULT init(string, ENEMYDISCERN, int, POINT);
	void update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager);
	void Hit();

	void Eating(POINT playerpoint);
	void face();
	void attackface();
	void missileattack();
	void whisleattack(bulletManager* BulletManager);
	void hitmove();
	
	void sethp(int h) { _hp = h; }
	int gethp() { return _hp; }
	woodboss() {}
	~woodboss() {}
};

