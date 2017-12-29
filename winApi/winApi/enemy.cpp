#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init(void)
{
	return S_OK;
}

HRESULT enemy::init(string imageName, ENEMYDISCERN discernNum, int appearMapNum, POINT pos)
{
	_image = IMAGEMANAGER->findImage(imageName);
	_discernNum = discernNum;
	_appearMapNum = appearMapNum;
	_x = pos.x;
	_y = pos.y;
	_framex = 0;
	_framey = 0;

	_ani = new animation;
	
	_frameTimer = TIMEMANAGER->getWorldTime();
	_frameWorldTimer = TIMEMANAGER->getWorldTime();

	_hitCount = false;
	_hitTimer = TIMEMANAGER->getWorldTime();
	_hitWorldTimer = TIMEMANAGER->getWorldTime();
	_moveselect = false;
	_collisioncheck = false;
	_anicheck = true;
	//true 일경우 rect이동
	_burningselect = true;
	//true일 경우 공격중.
	_attactmotion = false;
	//먹는함수 true 일 경우 먹힘
	_eating = false;
	_rectcheck = true;
	_gravity = 3.0f;


	return S_OK;
}

void enemy::release(void)
{
	SAFE_DELETE(_ani);
}

void enemy::update(image* pixelimage, POINT playerPoint, vector<fieldObject*> objectVec, vector<bullet*> bulletVec, bulletManager* BulletManager)
{
	

}

void enemy::pixelcollision(image * pixelimage, vector<fieldObject*> objectVec)
{
	
	
	//충돌 - 아래
	for (int i =_rc.bottom; i > _rc.bottom - 1; i--)
	{
		COLORREF color = GetPixel(pixelimage->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			
			_collisioncheck = true;
			_state = 1;
			break;
		}
		else if (!(r == 255 && g == 0 && b == 0))
		{

			_collisioncheck = false;
			_state = 1;
			break;
		}
	}


	//충돌 좌우
		for (int i = _rc.right; i > _rc.right - 1; i--)
		{

			COLORREF color = GetPixel(pixelimage->getMemDC(), i, _y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 0)
			{

				if (_dr == drright)
				{
					_dr = drleft;
				}
				break;
			}
		}
		for (int i = _rc.left; i > _rc.left - 1; i--)
		{

			COLORREF color = GetPixel(pixelimage->getMemDC(), i, _y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 0)
			{

				if (_dr == drleft)
				{
					_dr = drright;
				}
				break;
			}
		}
	if (!_collisioncheck)
	{
		_y += _gravity;
	}

	
}

void enemy::brontocollision(image * pixelimage, vector<fieldObject*> objectVec)
{


	for (int i = _rc.bottom; i > _rc.bottom - 1; i--)
	{
		COLORREF color = GetPixel(pixelimage->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{

			_collisioncheck = true;
			_state = 1;
			break;
		}
		else
		{
			_collisioncheck = false;

		}
	}


	if (!_collisioncheck)
	{
		_y += _gravity;
	}

}

