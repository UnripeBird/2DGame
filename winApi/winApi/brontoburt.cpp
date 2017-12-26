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
	_framex = 0;
	_framey = 3;
	_dr = drright;
	return S_OK;
}

void brontoburt::update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec)
{
	_hitWorldTimer = TIMEMANAGER->getWorldTime();
	_frameWorldTimer = TIMEMANAGER->getWorldTime();
	//움직이는 방향
	
	if (playerPoint.x < _rezen.x && _moveselect == false)
	{
		_dr = drleft;

	}
	else if (playerPoint.x > _rezen.x && _moveselect == false)
	{
		_dr = drright;
	}

	if (getDistance(playerPoint.x, playerPoint.y, _x, _y) < 200)
	{
		_moveselect = true;

	}

	//움직임

		if (_hitCount == false && _moveselect == true && _state == 1)
		{

			//상하이동 움직임 조정 
			if (_sitdown == true)
			{
			
				if (_framex < 1)
				{
					_framey = 3;
					switch (_dr)
					{
					case drright:
					{

						_framey = 3;
					}
					break;
					case drleft:
					{

						_framey = 2;
					}
					break;
					}

				}
			
				if (_framex >= 1)
				{

					if (_frameWorldTimer - _frameTimer > 1.0f)
					{
						_frameTimer = TIMEMANAGER->getWorldTime();
						_framex++;

						if (_image->getMaxFrameX() < _framex)
						{
							_framex = 0;
						}

					}

					switch (_dr)
					{
					case drright:
					{
						_y -= _moveSpeed;
						_framey = 1;
					}
					break;
					case drleft:
					{
						_y -= _moveSpeed;
						_framey = 0;
					}
					break;
					}
					if (getDistance(_rezen.x, _rezen.y, _x, _y) > 100)
					{
						_sitdown = false;
					}
				}
				if (_framex == 0)
				{
					if (_frameWorldTimer - _frameTimer > 0.5f)
					{
						_frameTimer = TIMEMANAGER->getWorldTime();
						_framex++;
						if (_image->getMaxFrameX() < _framex)
						{
							_framex = 1;

						}
					}
				}

			}

			//좌우 이동 
			else if (_sitdown == false && _state == 1)
			{
				if (_frameWorldTimer - _frameTimer > 0.25f)
				{
					_frameTimer = TIMEMANAGER->getWorldTime();
					_framex++;
					if (_image->getMaxFrameX() < _framex)
					{
						_framex = 0;
					}
				}

				switch (_dr)
				{
				case drright:
				{
					_x += _moveSpeed;
					_framey = 1;
				}
				break;
				case drleft:
				{
					_x -= _moveSpeed;
					_framey = 0;
				}
				break;
				}
			}
		}


		//피격
		if (_hitCount == true && _moveselect == true)
		{



			if (_framey == 0)
			{
				_framey = 4;
				_framex = 0;


			}

			else if (_framey == 1)
			{
				_framey = 4;
				_framex = 1;

			}
			if (_hitWorldTimer - _hitTimer > 1.0f && _framex == 0)
			{

				_framey = 0;
				_hitCount = false;
				_state = 2;

			}
			else if (_hitWorldTimer - _hitTimer > 1.0f && _framex == 1)
			{
				_framex = 0;
				_framey = 1;
				_hitCount = false;
				_state = 2;
			}
		}





		brontocollision();
		_rc = RectMakeCenter(_x, _y, 50, 50);
	

}

void brontoburt::Hit()
{

	_hitCount = true;

	_hitTimer = TIMEMANAGER->getWorldTime();

}
