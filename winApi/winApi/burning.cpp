#include "stdafx.h"	em = new burning;	em = new burning;	em = new burning;	em = new burning;
	em->init("버닝", Burning, 2, PointMake(900, 0));
	_vEnemy.push_back(em);
	em->init("버닝", Burning, 2, PointMake(900, 0));
	_vEnemy.push_back(em);
	em->init("버닝", Burning, 2, PointMake(900, 0));
	_vEnemy.push_back(em);
	em->init("버닝", Burning, 2, PointMake(900, 0));
	_vEnemy.push_back(em);
#include "burning.h"



HRESULT burning::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{

	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;

	_rezen = pos;
	_state = 0;
	_dr = drright;
	_framey = 0;
	_framex = -1;
	_ani->init(933 * 3, 600 * 3, 200, 100 * 3);
	_ani->setPlayFrame(0, 3, false, true);
	_ani->setFPS(3);
	_ani->start();
	return S_OK;
}

void burning::update(image * pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec)
{

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_hitWorldTimer = TIMEMANAGER->getWorldTime();


	//움직이는 방향

	//움직임
	if (!_collisioncheck)
	{
		_y += _moveSpeed;
	}
	if (_hitCount == false && _collisioncheck == true && _state == 1 && _attactmotion == false)
	{
	
			switch (_dr)
			{
			case drright:
			{
				if (_wallright == true)
				{
					_y -= _moveSpeed;
				}
				if (_wallleft == true && _wallright == false && _collisioncheck == false)
				{
					_y += _moveSpeed;
				}
				else
				{
					_x += _moveSpeed;
				}
				move();
			
			}
			break;
			case drleft:
			{
			

			}
			break;
			case drup:
			{
				move();
				_y -= _moveSpeed;
			}
			break;
			case drdown:
			{
				move();
				_y += _moveSpeed;
			}
			break;
			}
	
	
	
	
	}


	//피격
	if (_hitCount == true && _state == 1)
	{
		hitmove();
		if (_hitWorldTimer - _hitTimer > 1.0f)
		{
			_hitCount = false;
			_state = 2;

		}
	
	}

	//공격

	if (getDistance(playerPoint.x, playerPoint.y, _x, _y) < 200)
	{
	//	_attactmotion = true;

	}
	if (_attactmotion == true)
	{
	
		if (_ani->isPlay() == false)
		{
			_anicheck = false;
			_attactmotion = false;
		}
	}
	_rc = RectMakeCenter(_x, _y, 50, 50);
	//좌
	_probe[0] = RectMakeCenter(_rc.left-5, _rc.bottom-(_rc.bottom-_rc.top)/2, 10, 10);
	//우
	_probe[1] = RectMakeCenter(_rc.right+5, _rc.bottom - (_rc.bottom - _rc.top) / 2, 10, 10);
	//상
	_probe[2] = RectMakeCenter(_rc.right-(_rc.right - _rc.left)/2, _rc.top - 5, 10, 10);
	//하
	_probe[3] = RectMakeCenter(_rc.right - (_rc.right - _rc.left) / 2, _rc.bottom + 5, 10, 10);
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


void burning::attackmoveleft()
{

	_ani->setPlayFrame(14, 27, false, true);
	_ani->setFPS(3);
	
}

void burning::attackmoveright()
{
	_ani->setPlayFrame(28, 41, false, true);
	_ani->setFPS(3);
	
}

void burning::hitmove()
{

	_ani->setPlayFrame(42, 42, false, true);
	_ani->setFPS(3);
	_ani->start();
}
