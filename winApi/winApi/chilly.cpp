#include "stdafx.h"
#include "chilly.h"

HRESULT chilly::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;

	_rezen = pos;
	_state = 0;
	_framex = -1;
	_ani->init(533 * 3, 300 * 3, 199, 100 * 3);
	_ani->setPlayFrame(0, 5, false, true);
	_ani->setFPS(3);
	_ani->start();

	return S_OK;
}

void chilly::update(image * pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec)
{

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_hitWorldTimer = TIMEMANAGER->getWorldTime();
	//움직이는 방향
	pixelcollision();
	//움직임

	if (_hitCount == false && _collisioncheck == true && _state == 1 && _attactmotion == false)
	{

		chillymove();
	}
	//피격
	if (_hitCount == true && _state == 1)
	{

		switch (_dr)
		{
		case drright:
		{
			hitmoveright();


			if (_hitWorldTimer - _hitTimer > 1.0f)
			{
				_hitCount = false;
				_state = 2;

			}

		}
		break;
		case drleft:
		{
			hitmoveleft();

			if (_hitWorldTimer - _hitTimer > 1.0f)
			{
				_hitCount = false;
				_state = 2;

			}
		}
		break;

		}

	}

	//공격

	if (getDistance(playerPoint.x, playerPoint.y, _x, _y) < 200)
	{
		_attactmotion = true;

	}
	if (_attactmotion == true)
	{
		attackmove();
		if (_ani->isPlay() == false)
		{
			_anicheck = false;
			_attactmotion = false;
		}
	}
	_rc = RectMakeCenter(_x, _y, 50, 50);
}

void chilly::Hit()
{
	_hitCount = true;

	_hitTimer = TIMEMANAGER->getWorldTime();
}

void chilly::chillymove()
{
	_ani->setPlayFrame(0, 5, false, true);
	_ani->setFPS(3);
	
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void chilly::attackmove()
{
	_ani->setPlayFrame(attackarr, 24, false);
	_ani->setFPS(5);

}

void chilly::hitmoveleft()
{
	_ani->setPlayFrame(16, 16, false, true);
	_ani->setFPS(3);
	_ani->start();
}

void chilly::hitmoveright()
{
	_ani->setPlayFrame(17, 17, false, true);
	_ani->setFPS(3);
	_ani->start();
}
