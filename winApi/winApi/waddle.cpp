#include "stdafx.h"
#include "waddle.h"


HRESULT waddle::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;
	
	_rezen = pos;
	_state = 0;
	_framex = -1;
	_ani->init(266 * 3, 600 * 3, 199, 100 * 3);
	_ani->setPlayFrame(4, 7, false, true);
	_ani->setFPS(3);
	_ani->start();

	_dr =drright;

	return S_OK;
}

void waddle::update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager)
{
	
	_hitWorldTimer = TIMEMANAGER->getWorldTime();
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	//움직임
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

	if (_hitCount == false)
	{
			pixelcollision(pixelimage, objectVec);

	}
	death(bulletVec);

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
//피격함수
void waddle::Hit()
{
	_ani->stop();
	_hitCount = true;

	_hitTimer = TIMEMANAGER->getWorldTime();

}

void waddle::moveright()
{
	_ani->setPlayFrame(4, 7, false, true);
	_ani->setFPS(3);

	if (_ani->isPlay() == false)
	{
		_ani->start();
	}

}

void waddle::moveleft()
{
	_ani->setPlayFrame(0, 3, false, true);
	_ani->setFPS(3);

	if (_ani->isPlay() == false)
	{
		_ani->start();
	}

}

void waddle::hitright()
{
	_ani->setPlayFrame(9, 9, false, true);
	_ani->setFPS(3);

	if (_ani->isPlay() == false)
	{
		_ani->start();
	}

}

void waddle::hitleft()
{
	_ani->setPlayFrame(8, 8, false, true);
	_ani->setFPS(3);

	if (_ani->isPlay() == false)
	{
		_ani->start();
	}

}

void waddle::Eating(POINT playerpoint)
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

void waddle::death(vector<bullet*> bulletVec)
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
