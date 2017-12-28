#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("�͵��", "enemy/waddle.bmp", 266*3, 600*3, 4, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "enemy/frog.bmp", 333*3, 300*3, 5, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����","enemy/bronto.bmp", 200 * 3, 500 * 3, 3, 5, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("����ũ", "enemy/spark.bmp", 1000 * 3, 400 * 3, 15, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ĥ��", "enemy/chilly.bmp", 533 * 3, 300 * 3, 8, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "enemy/burning.bmp", 933*3, 600*3, 14, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����ص�", "image/treeboss.bmp", 200 * 3, 380 * 3, 5, 5, true, RGB(255, 0, 255));
	enemy* em;
	em = new waddle;
	em->init("�͵��", waddledee, 0, PointMake(900, 100));
	_vEnemy.push_back(em);

	em = new frog;
	em->init("������", Frog, 0, PointMake(1000, 400));
	_vEnemy.push_back(em);

	em = new brontoburt;
	em->init("�����", Bronto, 0, PointMake(1500, 400));
	_vEnemy.push_back(em);

	em = new spark;
	em->init("����ũ", Spark, 0, PointMake(1000, -500));
	_vEnemy.push_back(em);

	em = new chilly;
	em->init("ĥ��", Chilly, 0, PointMake(600, 300));
	_vEnemy.push_back(em);

	em = new burning;
	em->init("����", Burning, 0, PointMake(900, 400));
	_vEnemy.push_back(em);

	em = new woodboss;
	em->init("�����ص�", treeboss, 3, PointMake(700, 500));
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

void enemyManager::update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, int curMapNum, bulletManager* BulletManager)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		if (curMapNum == (*_viEnemy)->getAppearMapNum())
		{
			(*_viEnemy)->update(pixelimage, playerPoint, objectVec, bulletVec, BulletManager);
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
		else
		{
			++_viEnemy;
		}
	}
}

