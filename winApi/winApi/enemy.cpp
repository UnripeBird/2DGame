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
	_framex = 0;
	_framey = 0;
	
	_frameTimer = TIMEMANAGER->getWorldTime();
	_frameWorldTimer = TIMEMANAGER->getWorldTime();

	_hitCount = false;
	_hitTimer = TIMEMANAGER->getWorldTime();
	_hitWorldTimer = TIMEMANAGER->getWorldTime();


	return S_OK;
}

void enemy::release(void)
{
}

void enemy::update(void)
{
	

}


