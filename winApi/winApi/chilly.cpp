#include "stdafx.h"
#include "chilly.h"

HRESULT chilly::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;

	_rezen = pos;
	_state = 0;

	_ani->init(1000 * 3, 400 * 3, 200, 100 * 3);
	_ani->setPlayFrame(0, 3, false, true);
	_ani->setFPS(3);
	_ani->start();
	return S_OK;
}

void chilly::update(image * pixelimage, POINT playerPoint)
{

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_hitWorldTimer = TIMEMANAGER->getWorldTime();
	//움직이는 방향
	pixelcollision();
	//움직임

	if (_hitCount == false && _collisioncheck == true && _state == 1 && _attactmotion == false)
	{

		switch (_dr)
		{
		case drright:
		{
			rightmove();
			_x += _moveSpeed;
		}
		break;
		case drleft:
		{
			leftmove();
			_x -= _moveSpeed;
		}
		break;
		}
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

	if (getDistance(playerPoint.x, playerPoint.y, _x, _y) < 50)
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
	_ani->setPlayFrame(15, 18, false, true);
	_ani->setFPS(3);
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void chilly::attackmove()
{
	_ani->setPlayFrame(attackarr, 16, false);
	_ani->setFPS(10);

}

void chilly::hitmoveleft()
{
	_ani->setPlayFrame(30, 30, false, true);
	_ani->setFPS(3);
	_ani->start();
}

void chilly::hitmoveright()
{
	_ani->setPlayFrame(31, 31, false, true);
	_ani->setFPS(3);
	_ani->start();
}
