
#include "stdafx.h"
#include "burning.h"

HRESULT burning::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{

	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;
	_burningselect = false;
	_rezen = pos;
	_state = 1;
	_dr = drright;
	_framey = 0;
	_framex = -1;
	_ani->init(933 * 3, 600 * 3, 200, 100 * 3);
	_ani->setPlayFrame(0, 3, false, true);
	_ani->setFPS(3);
	_ani->start();
	return S_OK;
}

void burning::update(image * pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager)
{

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_hitWorldTimer = TIMEMANAGER->getWorldTime();
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

	death(bulletVec);
	if (_hitCount == false &&_state == 1 && _attactmotion == false && _burningselect == false)
	{
		move();
	}
	//방향좌표
	if (getDistance(playerPoint.x, playerPoint.y, _x, _y) < 200 && _burningselect == false)
	{
		if (_hitCount == false && _attactmotion == false && _moveselect == false)
		{
			if (playerPoint.x > _x)
			{
				_dr = drright;
				_moveselect = true;
			
			}
			else if (playerPoint.x < _x)
			{
				_dr = drleft;
				_moveselect = true;
			}
			_attactmotion = true;
			_burningselect = true;
		}
		
	}
	
	if (_hitCount == false && _attactmotion == true && _burningselect== true)
	{
	
		switch (_dr)
		{
		case drright:
		{
			attackmoveright();
			_x += _moveSpeed;
			if (getDistance(_rezen.x, _rezen.y, _x, _y) > 250)
			{
				_ani->stop();
				_attactmotion = false;
				_burningselect = false;
				_moveselect = false;
				_rezen.x = _x;
				_rezen.y = _y;
			}
		}
		break;
		case drleft:
		{
			attackmoveleft();
			_x -= _moveSpeed;
			if (getDistance(_rezen.x, _rezen.y, _x, _y) > 250)
			{
				_ani->stop();
				_attactmotion = false;
				_burningselect = false;
				_moveselect = false;
				_rezen.x = _x;
				_rezen.y = _y;
			}
		}
		break;

		}
	
	
	}
	if (_hitCount == true)
	{
		if (_state == 1)
		{
			hitmove();
			if (_hitWorldTimer - _hitTimer > 1.0f)
			{
				_state = 2;
			}
		}
		else if (_state == 3)
		{
			hitmove();
		}
	}

	_rc = RectMakeCenter(_x, _y, 50, 50);
}

void burning::Hit()
{
	_hitCount = true;

	_hitTimer = TIMEMANAGER->getWorldTime();
}

void burning::move()
{
	_ani->setPlayFrame(0, 3, false, true);
	_ani->setFPS(3);
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void burning::Eating(POINT playerpoint)
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


void burning::attackmoveleft()
{

	_ani->setPlayFrame(14, 27, false, true);
	_ani->setFPS(2);

	if (_ani->isPlay() == false)
	{
		_ani->start();

	}
	
}

void burning::attackmoveright()
{
	_ani->setPlayFrame(28, 41, false, true);
	_ani->setFPS(2);

	if (_ani->isPlay() == false)
	{
		_ani->start();
		
	}
}

void burning::hitmove()
{

	_ani->setPlayFrame(13, 13, false, true);
	_ani->setFPS(3);
	_ani->start();

}

void burning::death(vector<bullet*> bulletVec)
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
