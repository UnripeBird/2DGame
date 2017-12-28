#include "stdafx.h"
#include "woodboss.h"

HRESULT woodboss::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;

	_rezen = pos;
	_state = 0;
	
	_framey = 0;
	_framex = -1;
	_whisle = false;
	_missile = false;
	_hp = 10;
	_ani->init(200 * 3, 380 * 3, 120, 76 * 3);
	_ani->setPlayFrame(0, 1, false, true);
	_ani->setFPS(3);
	_ani->start();
	_attacktimer = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void woodboss::update(image * pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager)
{
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_hitWorldTimer = TIMEMANAGER->getWorldTime();


	
	
	/*if (_hitWorldTimer - _attacktimer > 1.0f)
	{
		
		_whisle = true;
		attackface();
		//whisleattack(BulletManager);
	}
//	whisleattack(BulletManager);*/
	if (_whisle == false && _hitCount == false)
	{
		face();
	}
	if (_hitCount == true)
	{
		hitmove();


		if (_hitWorldTimer - _hitTimer > 1.0f)
		{
			_hitCount = false;
			

		}
	}

	_rc = RectMakeCenter(_x+30, _y+50, 250, 500);

}

void woodboss::Hit()
{
	_hitCount = true;

	_hitTimer = TIMEMANAGER->getWorldTime();
}

void woodboss::Eating(POINT playerpoint)
{
}

void woodboss::face()
{

	_ani->setPlayFrame(5, 8, false, true);
	_ani->setFPS(3);
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void woodboss::attackface()
{
	_ani->setPlayFrame(15, 17, false, true);
	_ani->setFPS(3);
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void woodboss::hitmove()
{
	_ani->setPlayFrame(10, 14, false, true);
	_ani->setFPS(3);
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}
void woodboss::missileattack()
{
		
}
void woodboss::whisleattack(bulletManager* BulletManager)
{	
	_attacktimer = TIMEMANAGER->getWorldTime();


	BulletManager->enemyFire(BossBreath, PointMake(700,600));
	

	if (_ani->isPlay() == false)
	{
		_whisle = false;
	}

}

