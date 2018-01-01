#include "stdafx.h"
#include "woodboss.h"

HRESULT woodboss::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;

	_rezen = pos;
	_state = 1;
	
	_framey = 0;
	_framex = -1;
	_whisle = false;
	_missile = false;
	_atkreset = false;
	_livecheck = true;
	_hp = 10;
	_ani->init(200 * 3, 380 * 3, 120, 76 * 3);
	_ani->setPlayFrame(0, 1, false, true);
	_ani->setFPS(3);
	_ani->start();

	_attacktimer = TIMEMANAGER->getWorldTime();
	_missileTimer = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void woodboss::update(image * pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager)
{
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_hitWorldTimer = TIMEMANAGER->getWorldTime();
	//보스 입냄새 공격 사거리 길게 늘리기
	
	if (_hp <= 0)
	{
		_ani->stop();
		hitmove();
		if (_hitWorldTimer - _hitTimer > 1.0f)
		{	
			_livecheck = false;
			_hitCount = false;
			_state = 2;

		}
	
	}
	if (_livecheck == true)
	{
		underattack(bulletVec);
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
				_ani->stop();

			}
		}
		//공격 모션
		if (_hitWorldTimer - _attacktimer > 5.0f)
		{
			if (_ani->isPlay() == true)
			{
				_ani->stop();
			}
			attackface();
			if (_atkreset == false)
			{
				_whisle = true;
				_atkreset = true;
			}

			if (_hitWorldTimer - _attacktimer > 7.0f)
			{
				_attacktimer = TIMEMANAGER->getWorldTime();
				_atkreset = false;
			}


		}

		if (_hitWorldTimer - _missileTimer > 2.0f)
		{
			if (_missile == false)
			{

				if (_hitWorldTimer - _missileTimer > 3.0f)
				{
					_missileTimer = TIMEMANAGER->getWorldTime();
					_missile = true;
				}
			}


		}



		if (_whisle == true)
		{
			whisleattack(BulletManager);
			_whisle = false;

		}

		if (_missile == true)
		{
			for (int i = 0; i < 10; i++)
			{
				missileattack(BulletManager, i, playerPoint);

			}
			_missile = false;
		}
		_rc = RectMakeCenter(_x + 30, _y + 50, 250, 500);

	}
		
}


void woodboss::Hit()
{
	_ani->stop();
	_hitCount = true;

	_hitTimer = TIMEMANAGER->getWorldTime();
	_hp -= 1;
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
void woodboss::underattack(vector<bullet*> bulletVec)
{
	for (int i = 0; i < bulletVec.size(); i++)
	{
		RECT rctemp;
		if (IntersectRect(&rctemp, &bulletVec[i]->getrc(), &_rc))
		{
			Hit();
			bulletVec[i]->setState(2);
		}

	}
}
void woodboss::missileattack(bulletManager* BulletManager,int x, POINT playerPoint)
{
	
		BulletManager->enemyFire(BossApple, PointMake(x* 80, 200), getAngle(x*80, 200, playerPoint.x, playerPoint.y));

	
	
	
}
void woodboss::whisleattack(bulletManager* BulletManager)
{	
	
	BulletManager->enemyFire(BossBreath, PointMake(700,700));
	
}
