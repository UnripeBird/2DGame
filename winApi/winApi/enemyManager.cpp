#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("와들디", "enemy/waddle.bmp", 266*3, 600*3, 4, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("슬리피", "enemy/frog.bmp", 333*3, 300*3, 5, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("브론토","enemy/bronto.bmp", 200 * 3, 500 * 3, 3, 5, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("스파크", "enemy/spark.bmp", 1000 * 3, 400 * 3, 15, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("칠리", "enemy/chilly.bmp", 533 * 3, 300 * 3, 8, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("버닝", "enemy/burning.bmp", 933*3, 600*3, 14, 6, true, RGB(255, 0, 255));

	enemy* em;
	em = new waddle;
	em->init("와들디", waddledee, 0, PointMake(900, 100));
	_vEnemy.push_back(em);

	em = new frog;
	em->init("슬리피", Frog, 0, PointMake(1000, 400));
	_vEnemy.push_back(em);

	em = new brontoburt;
	em->init("브론토", Bronto, 0, PointMake(1500, 400));
	_vEnemy.push_back(em);

	em = new spark;
	em->init("스파크", Spark, 0, PointMake(1000, -500));
	_vEnemy.push_back(em);

	em = new chilly;
	em->init("칠리", Chilly, 0, PointMake(600, 300));
	_vEnemy.push_back(em);

	em = new burning;
	em->init("버닝", Burning, 0, PointMake(600, 300));
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

void enemyManager::update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		(*_viEnemy)->update(pixelimage, playerPoint, objectVec, bulletVec);
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

