#include "stdafx.h"
#include "boxEnemy.h"

HRESULT boxEnemy::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	enemy::init(imageName, discernNum, appearMapNum, pos);
	_boxSpeed = 0.0f;
	_acceleration = 0.1f;
	return S_OK;
}

void boxEnemy::update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager)
{

	_x += _boxSpeed;
	_boxSpeed += _acceleration;
	
	if (_boxSpeed >= 5.0f) _acceleration = -0.1f;
	else if (_boxSpeed <= -5.0f) _acceleration = 0.1f;

	_rc = RectMakeCenter(_x, _y, 100, 100);
}
