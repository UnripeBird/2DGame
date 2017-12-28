#pragma once
#include "enemy.h"
class boxEnemy : public enemy
{
private:
	float _boxSpeed;
	float _acceleration;

public:
	HRESULT init(string, ENEMYDISCERN, int, POINT);
	void update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager);

	boxEnemy() {}
	~boxEnemy() {}
};

