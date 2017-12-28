#pragma once
#include "enemy.h"
class burning :
	public enemy
{
private:

	float _moveSpeed;

	POINT _rezen;

public:
	HRESULT init(string, ENEMYDISCERN, int, POINT);
	void update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager);
	void Hit();

	void move();
	void Eating(POINT playerpoint);

	void attackmoveleft();
	void attackmoveright();
	void hitmove();
	void death(vector<bullet*> bulletVec);
	burning() {}
	~burning() {}
};

