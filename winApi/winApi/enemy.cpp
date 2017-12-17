#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init(void)
{
	return S_OK;
}

HRESULT enemy::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	_image = IMAGEMANAGER->findImage(imageName);
	_discernNum = discernNum;
	_appearMapNum = appearMapNum;
	_x = pos.x;
	_y = pos.y;

	return S_OK;
}

void enemy::release(void)
{
}

void enemy::update(void)
{
}
