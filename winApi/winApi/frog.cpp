#include "stdafx.h"
#include "frog.h"


HRESULT frog::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;

	_rezen = pos;
	_state = 0;
	_framex = -1;
	_dr = drright;
	_ani->init(333 * 3, 300 * 3, 199, 100 * 3);
	_ani->setPlayFrame(5, 9, false, true);
	_ani->setFPS(3);
	_ani->start();

	return S_OK;
}

void frog::update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager)
{

	_hitWorldTimer = TIMEMANAGER->getWorldTime();
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
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
	//if (_hitCount == false)
	//{
	//	pixelcollision(pixelimage, objectVec);
	//
	//}
	if (_hitCount == false)
	{
		pixelcollision(pixelimage, objectVec);

	}
	death(bulletVec);
	//움직임
	if (_hitCount == false && _state == 1)
	{
	
		switch (_dr)
		{
		case drright:
		{
			moveright();
			_x += _moveSpeed;
	
		}
		break;
		case drleft:
		{
			moveleft();
			_x -= _moveSpeed;
		
		}
		break;
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
				hitright();
			}
			break;
			case drleft:
			{
				hitleft();
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
				hitright();
			}
			break;
			case drleft:
			{
				hitleft();
			}
			break;

			}
		}
	}


	_rc = RectMakeCenter(_x, _y, 50, 50);
}

void frog::Hit()
{
	_ani->stop();
	_hitCount = true;

	_hitTimer = TIMEMANAGER->getWorldTime();

}

void frog::moveright()
{
	_ani->setPlayFrame(5, 9, false, true);
	_ani->setFPS(3);

	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void frog::moveleft()
{
	_ani->setPlayFrame(0, 4, false, true);
	_ani->setFPS(3);

	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void frog::hitright()
{
	_ani->setPlayFrame(11, 11, false, true);
	_ani->setFPS(3);

	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void frog::hitleft()
{
	_ani->setPlayFrame(10, 10, false, true);
	_ani->setFPS(3);

	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void frog::Eating(POINT playerpoint)
{
	_ani->stop();
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

void frog::death(vector<bullet*> bulletVec)
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
