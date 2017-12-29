#include "stdafx.h"
#include "chilly.h"

HRESULT chilly::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;
	
	_rezen = pos;
	_state = 1;
	_framex = -1;
	_ani->init(533 * 3, 300 * 3, 199, 100 * 3);
	_ani->setPlayFrame(0, 5, false, true);
	_ani->setFPS(3);
	_ani->start();
	_dr = drright;
	return S_OK;
}

void chilly::update(image * pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager)
{

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_hitWorldTimer = TIMEMANAGER->getWorldTime();
	//움직이는 방향
	//for (int i = 0; i < objectVec.size(); i++)
	//{
	//	if (IntersectRect(&_rctemp, &objectVec[i]->getrc(), &_rc) && objectVec[i]->getAppearMapNum() == _appearMapNum)
	//	{
	//		_rectcheck = true;
	//		_collisioncheck = true;
	//		_state = 1;
	//		break;
	//	}
	//	else
	//	{
	//		_rectcheck = false;
	//		_collisioncheck = false;
	//	}
	//
	//}

	
	if (_hitCount == false)
	{
		pixelcollision(pixelimage, objectVec);

	}
	death(bulletVec);
	//움직임
	if (playerPoint.x > _x)
	{
		_dr = drright;

	}
	else if (playerPoint.x < _x)
	{
		_dr = drleft;
	}
	if (_hitCount == false && _collisioncheck == true && _state == 1 && _attactmotion == false)
	{

		chillymove();
		if (getDistance(playerPoint.x, playerPoint.y, _x, _y) < 200)
		{
			_attactmotion = true;


		}
	}
	//피격
	if (_hitCount == true)
	{

		_ani->start();
		if (_state == 1)
		{
			switch (_dr)
			{
			case drright:
			{
				hitmoveright();

			}
			break;
			case drleft:
			{
				hitmoveleft();

			}
			break;

			}
			if (_hitWorldTimer - _hitTimer > 1.0f)
			{
				_hitCount = false;
				_state = 2;

			}
		}
		else if (_state == 3)
		{
			switch (_dr)
			{
			case drright:
			{
				hitmoveright();

			}
			break;
			case drleft:
			{
				hitmoveleft();

			}
			break;

			}
		}
		

	}

	//공격

	
	if (_attactmotion == true)
	{
		attackmove();
		if (_ani->isPlay() == false)
		{
			_anicheck = false;
			_attactmotion = false;
		}
	}
	if (_attactmotion == true)
	{
		_rc = RectMakeCenter(_x, _y, 110, 150);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, 50, 50);
	}
}

void chilly::Hit()
{
	_ani->stop();
	_hitCount = true;

	_hitTimer = TIMEMANAGER->getWorldTime();
}

void chilly::Eating(POINT playerpoint)
{
	_hitCount = true;
	_state = 3;
	if (playerpoint.x > _x)
	{
		_x += _moveSpeed;
		if (playerpoint.y > _y)
		{
			_y += _moveSpeed;
		}
		else if (playerpoint.y < _y)
		{
			_y -= _moveSpeed;
		}
	}
	else if (playerpoint.x < _x)
	{
		_x -= _moveSpeed;
		if (playerpoint.y > _y)
		{
			_y += _moveSpeed;
		}
		else if (playerpoint.y < _y)
		{
			_y -= _moveSpeed;
		}
	}
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

	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void chilly::hitmoveright()
{
	_ani->setPlayFrame(17, 17, false, true);
	_ani->setFPS(3);

	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void chilly::death(vector<bullet*> bulletVec)
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
