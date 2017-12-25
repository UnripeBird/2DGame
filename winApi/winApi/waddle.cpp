#include "stdafx.h"
#include "waddle.h"


HRESULT waddle::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	enemy::init(imageName, discernNum, appearMapNum, pos);
	//이동속도 1.0
	_moveSpeed = 1.0f;
	
	_rezen = pos;
	_state = 0;
	_dr =drright;

	return S_OK;
}

void waddle::update(image* pixelimage, POINT playerPoint)
{
	
	_hitWorldTimer = TIMEMANAGER->getWorldTime();

	//움직임
	if (_hitCount == false && _state == 1)
	{
		_frameWorldTimer = TIMEMANAGER->getWorldTime();
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
	//피격
	if (_hitCount == true && _state == 1)
	{



		if (_framey == 0)
		{
			_framey = 2;
			_framex = 0;


		}

		else if (_framey == 1)
		{
			_framey = 2;
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




	pixelcollision();

	_rc = RectMakeCenter(_x, _y, 50, 50);
	
}
//피격함수
void waddle::Hit()
{

	_hitCount = true;

	_hitTimer = TIMEMANAGER->getWorldTime();

}
