#pragma once
#include "enemy.h"
class chilly :
	public enemy
{
private:

	float _moveSpeed;
	int attackarr[24] = {8,9,10,11,10,11,8,9,8,9,10,11,12,13,14,15,12,13,14,15,12,13,14,15 };
	
	POINT _rezen;

public:
	HRESULT init(string, ENEMYDISCERN, int, POINT);
	void update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager);
	void Hit();
	void Eating(POINT playerpoint);
	void chillymove();

	void attackmove();
	void hitmoveleft();
	void hitmoveright();
	void death(vector<bullet*> bulletVec);
	chilly() {}
	~chilly() {}
};

