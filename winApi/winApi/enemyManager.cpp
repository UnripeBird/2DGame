#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("�͵��", "enemy/waddle.bmp", 266*3, 600*3, 4, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "enemy/frog.bmp", 333*3, 300*3, 5, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����","enemy/bronto.bmp", 200 * 3, 500 * 3, 3, 5, true, RGB(0, 255, 0));
	enemy* em;
	em = new waddle;
	em->init("�͵��", waddledee, 0, PointMake(800, 400));
	_vEnemy.push_back(em);

	em = new frog;
	em->init("������", Frog, 0, PointMake(400, 400));
	_vEnemy.push_back(em);

	em = new brontoburt;
	em->init("�����", Bronto, 0, PointMake(800, 100));
	_vEnemy.push_back(em);
	return S_OK;
}

void enemyManager::release(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		(*_viEnemy)->release();
		SAFE_DELETE(*_viEnemy);
		_viEnemy = _vEnemy.erase(_viEnemy);
	}
}

void enemyManager::update(image* pixelimage, POINT playerPoint)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		(*_viEnemy)->update(pixelimage,playerPoint);
		if ((*_viEnemy)->getState() == 2)
		{
			(*_viEnemy)->release();
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else
		{
			++_viEnemy;
		}
	}
}

