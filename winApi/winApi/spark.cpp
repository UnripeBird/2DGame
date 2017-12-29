#include "stdafx.h"
#include "spark.h"




HRESULT spark::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;

	_rezen = pos;
	_state = 0;
	_dr = drright;

	_framex = -1;
	
	_ani->init(1000 * 3, 400 * 3,200, 100 * 3);
	_ani->setPlayFrame(0, 3, false, true);
	_ani->setFPS(3);
	_ani->start();
	return S_OK;
}

void spark::update(image * pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager)
{
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_hitWorldTimer = TIMEMANAGER->getWorldTime();
	//움직이는 방향
	//for (int i = 0; i < objectVec.size(); i++)
	//{
	//	if (IntersectRect(&_rctemp, &objectVec[i]->getrc(), &_rc))
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
	//if (_hitCount == false && _eating == false)
	//{
	//
	//}
	//움직임
	if (_hitCount == false)
	{
		pixelcollision(pixelimage, objectVec);

	}
	death(bulletVec);
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
		if (getDistance(playerPoint.x, playerPoint.y, _x, _y) < 100)
		{
			_attactmotion = true;

		}
	}
	//피격
	if (_hitCount == true)
	{
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
		_rc = RectMakeCenter(_x, _y, 100, 100);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, 50, 50);
	}
}

void spark::Hit()
{
	_hitCount = true;

	_hitTimer = TIMEMANAGER->getWorldTime();
}

void spark::Eating(POINT playerpoint)
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

void spark::rightmove()
{

		_ani->setPlayFrame(15, 18, false, true);
		_ani->setFPS(3);
		if (_ani->isPlay() == false)
		{
			_ani->start();
		}

	
}

void spark::leftmove()
{

	
		_ani->setPlayFrame(0, 3, false, true);
		_ani->setFPS(3);
		if (_ani->isPlay() == false)
		{
			_ani->start();
		}
	
}

void spark::attackmove()
{
	_ani->setPlayFrame(attackarr, 28, false);
	_ani->setFPS(10);

}

void spark::hitmoveleft()
{
	_ani->setPlayFrame(30, 30, false, true);
	_ani->setFPS(3);
	_ani->start();
}

void spark::hitmoveright()
{
	_ani->setPlayFrame(31, 31, false, true);
	_ani->setFPS(3);
	_ani->start();
}

void spark::death(vector<bullet*> bulletVec)
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

