#include "stdafx.h"
#include "bulletManager.h"

HRESULT bulletManager::init(void)
{
	IMAGEMANAGER->addFrameImage("kirbybreath", "image\\kirbybreath.bmp", 312*2, 24*2, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kirbystar", "image\\kirbystar.bmp", 96*2, 24*2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossbreath", "image\\bossbreath.bmp", 108*2, 20*2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossapple", "image\\bossapple.bmp", 160*2, 20*2, 8, 1, true, RGB(255, 0, 255));


	return S_OK;
}

void bulletManager::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		(*_viBullet)->release();
		_viBullet = _vBullet.erase(_viBullet);
	}

	for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end();)
	{
		(*_viEnemyBullet)->release();
		_viEnemyBullet = _vEnemyBullet.erase(_viEnemyBullet);
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

	for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end();)
	{
		(*_viEnemyBullet)->update();
		if ((*_viEnemyBullet)->getState() == 2)
		{
			_viEnemyBullet = _vEnemyBullet.erase(_viEnemyBullet);
		}
		else
		{
			++_viEnemyBullet;
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

void bulletManager::enemyFire(BULLETDISCERN discernNum, POINT pos, float angle)
{
	bullet* bt;
	bt = new bullet;

	bt->init(discernNum, pos, true, angle);
	_vEnemyBullet.push_back(bt);
}
