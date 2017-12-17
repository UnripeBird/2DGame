#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init(void)
{
	

	enemy* em;
	em = new boxEnemy;
	em->init("¾øÀ½", enemyBox, 0, PointMake(100, 400));
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

void enemyManager::update(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		(*_viEnemy)->update();
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