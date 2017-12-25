#include "stdafx.h"
#include "burning.h"



HRESULT burning::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{

	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;

	_rezen = pos;
	_state = 0;
	_framey = 0;
	return S_OK;
}

void burning::update(image * pixelimage, POINT playerPoint)
{
	_hitWorldTimer = TIMEMANAGER->getWorldTime();
	//움직이는 방향
	if (getDistance(_rezen.x, _rezen.y, _x, _y) <= 0)
	{
		_dr = drleft;

	}
	else if (getDistance(_rezen.x, _rezen.y, _x, _y) > 400)
	{
		_dr = drright;
	}

	//움직임
	if (_hitCount == false)
	{
		_frameWorldTimer = TIMEMANAGER->getWorldTime();
		if (_frameWorldTimer - _frameTimer > 0.25f)
		{
			_frameTimer = TIMEMANAGER->getWorldTime();
			_framex++;
			if (3 < _framex)
			{
				_framex = 0;
			}
		}

		switch (_dr)
		{
		case drright:
		{
			_x += _moveSpeed;
		
		}
		break;
		case drleft:
		{
			_x -= _moveSpeed;
		
		}
		break;
		}
	}
	//피격
	if (_hitCount == true)
	{



		if (_framey == 0)
		{
			_framey = 3;
			_framex = 0;


		}

		if (_hitWorldTimer - _hitTimer > 1.0f && _framex == 0)
		{

			_framey = 0;
			_hitCount = false;

		}
		else if (_hitWorldTimer - _hitTimer > 1.0f && _framex == 1)
		{
			_framex = 0;
			_framey = 0;
			_hitCount = false;
		}
	}

	_rc = RectMakeCenter(_x, _y, 50, 50);
}

void burning::Hit()
{
	_hitCount = true;

	_hitTimer = TIMEMANAGER->getWorldTime();
}
