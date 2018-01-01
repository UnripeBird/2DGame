#include "stdafx.h"
#include "brontoburt.h"


HRESULT brontoburt::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;

	_rezen = pos;
	_state = 0;
	_sitdown = true;
	_framex = -1;
	_triangle = 0;
	_dr = drright;
	_ani->init(200 * 3, 500 * 3, 200, 100 * 3);
	_ani->setPlayFrame(4, 4, false, true);
	_ani->setFPS(3);
	_ani->start();
	return S_OK;
}

void brontoburt::update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager)
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

	if (_hitCount == false && _moveselect == false)
	{
		brontocollision(pixelimage, objectVec);

	}
	death(bulletVec);
	//움직이는 방향
	_triangle++;
	if (_triangle > 180)
	{
		_triangle = 0;
	}
	if (playerPoint.x < _rezen.x && _moveselect == false)
	{
		_dr = drleft;

	}
	else if (playerPoint.x > _rezen.x && _moveselect == false)
	{
		_dr = drright;
	}


	//움직임 판정

		if (_hitCount == false && _state == 1 && _moveselect == false)
		{

			//상하이동 움직임 조정 
			if (_sitdown == true)
			{
				switch (_dr)
				{
				case drright:
				{
					sitright();
				}
				break;
				case drleft:
				{
					sitleft();
				}
				break;
				}

				if (getDistance(playerPoint.x, playerPoint.y, _x, _y) < 200)
				{
					_sitdown = false;
					_moveselect = true;
				}

			}
		}

		//좌우 이동 

		if (_hitCount == false && _sitdown == false && _state == 1 && _moveselect == true)
		{
			if (getDistance(_rezen.x, _rezen.y, _x, _y) < 100)
			{
				switch (_dr)
				{
				case drright:
				{
					moveright();
					
				}
				break;
				case drleft:
				{
					moveleft();
				
				}
				break;
				}
				_y -= _moveSpeed;
			}
			else
			{
				switch (_dr)
				{
					case drright:
					{
						moveright();
						_x += _moveSpeed;
						_y += -sinf((PI / 90) * _triangle) * _moveSpeed;
					}
					break;
					case drleft:
					{
						moveleft();
						_x -= _moveSpeed;
						_y += -sinf((PI / 90) * _triangle) * _moveSpeed;
						
					}
					break;
				}
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

void brontoburt::Hit()
{

	_hitCount = true;

	_ani->stop();
	_hitTimer = TIMEMANAGER->getWorldTime();

}

void brontoburt::moveright()
{
	_ani->setPlayFrame(3, 5, false, true);
	_ani->setFPS(3);
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void brontoburt::moveleft()
{
	_ani->setPlayFrame(0, 2, false, true);
	_ani->setFPS(3);
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void brontoburt::hitright()
{
	_ani->setPlayFrame(12, 12, false, true);
	_ani->setFPS(3);
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void brontoburt::hitleft()
{
	_ani->setPlayFrame(13, 13, false, true);
	_ani->setFPS(3);
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void brontoburt::sitright()
{
	_ani->setPlayFrame(3, 3, false, true);
	_ani->setFPS(3);
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void brontoburt::sitleft()
{
	_ani->setPlayFrame(0, 0, false, true);
	_ani->setFPS(3);
	if (_ani->isPlay() == false)
	{
		_ani->start();
	}
}

void brontoburt::Eating(POINT playerpoint)
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

void brontoburt::death(vector<bullet*> bulletVec)
{
	
	for (int i = 0; i < bulletVec.size(); i++)
	{
		RECT rctemp;
		if (IntersectRect(&rctemp, &bulletVec[i]->getrc(), &_rc))
		{
			Hit();
			bulletVec[i]->setState(2);
			_ani->stop();
		}

	}
}
