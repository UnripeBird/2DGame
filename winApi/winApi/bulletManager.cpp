#include "stdafx.h"
#include "bulletManager.h"

HRESULT bulletManager::init(void)
{
	IMAGEMANAGER->addFrameImage("kirbybreath", "image\\kirbybreath.bmp", 312*2, 24*2, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kirbystar", "image\\kirbystar.bmp", 96*2, 24*2, 4, 1, true, RGB(255, 0, 255));

	return S_OK;
}

void bulletManager::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		(*_viBullet)->release();
		_viBullet = _vBullet.erase(_viBullet);
	}
}

void bulletManager::update(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		(*_viBullet)->update();
		if ((*_viBullet)->getState() == 2)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void bulletManager::bulletFire(BULLETDISCERN discernNum, POINT pos, bool leftRight)
{
	bullet* bt;
	bt = new bullet;

	bt->init(discernNum, pos, leftRight);
	_vBullet.push_back(bt);
}