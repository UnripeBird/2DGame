#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init(BULLETDISCERN discernNum, POINT pos, bool fireLeftRight)
{
	string imageName;
	switch (discernNum)
	{
		case Breath:
			imageName = "kirbybreath";
			break;
		case Star:
			imageName = "kirbystar";
			break;
	}
	_image = IMAGEMANAGER->findImage(imageName);
	_discernNum = discernNum;
	_startX = _x = pos.x;
	_startY = _y = pos.y;
	_fireLeftRight = fireLeftRight;

	_frameTimer = TIMEMANAGER->getWorldTime();
	_frameWorldTimer = TIMEMANAGER->getWorldTime();

	_frameX = 0;
	_frameY = 0;

	switch (discernNum)
	{
		case Breath:
			_speed = 2;
			_range = 150;
			break;
		case Star:
			_speed = 4;
			_range = 300;
			break;
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	return S_OK;
}

void bullet::release(void)
{
}

void bullet::update(void)
{
	_frameWorldTimer = TIMEMANAGER->getWorldTime();
	if (_frameWorldTimer - _frameTimer > 0.05f)
	{
		_frameTimer = TIMEMANAGER->getWorldTime();
		_frameX++;
		if (_frameX > _image->getMaxFrameX())
		{
			_frameX = 0;
		}
	}
	if (!_fireLeftRight)
	{
		_x += _speed;
	}
	else
	{
		_x -= _speed;
	}
	if (getDistance(_startX, _startY, _x, _y) > _range)
	{
		_state = 2;
	}
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}
