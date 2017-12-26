#include "stdafx.h"
#include "mobBox.h"

HRESULT mobBox::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{
	_appearMapNum = 0;
	_discernNum = mob;
	_x = 500.0f;
	_y = 300.0f;
	_rc = RectMakeCenter(_x, _y, 100, 100);

	fieldObject::init(objectName, discernNum, mapNum, pos);
	_image = IMAGEMANAGER->findImage("Áö·Ú");

	_objNumberX = 0;
	_objNumberY = 0;

	count = 0;
	mobCount = 0;
	circleCount = 0;

	circleBool = true;

	mobstruct.radius = 5;
	mobstruct.angle = PI / 180;

	_circleTimer = TIMEMANAGER->getWorldTime();

	_rand = rand->getInt(3);

	return S_OK;
}

void mobBox::update(POINT playerPosition, vector<bullet*> bulletPos)
{
	move();
	moving();
	if (_rand == 0)moving2();
	if(_rand == 1)moving01();
	if(_rand == 2)circle();

	for (int i = 0; i < bulletPos.size(); i++)
	{
		if (IntersectRect(&_rcTemp, &bulletPos[i]->getrc(), &_rc))
		{
			_effectBullet = true;
			bulletPos[i]->setState(2);
		}
	}

	if (_effectBullet)
	{
		bulletEffect();
	}

}

void mobBox::move()
{
	if (_image == NULL)
	{
		_rc = RectMakeCenter(_x, _y, 100, 100);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}
}

//ÁÂ¿ìÀÌµ¿
void mobBox::moving01()
{
	_circleWorldTimer = TIMEMANAGER->getWorldTime();
	if (circleBool)
	{
		if (_circleWorldTimer - _circleTimer < 2.0f)
		{
			_x++;
		}
		else
		{
			circleBool = false;
			_circleTimer = TIMEMANAGER->getWorldTime();
		}
	}
	if (!circleBool)
	{
		if (_circleWorldTimer - _circleTimer < 2.0f)
		{
			_x--;
		}
		else
		{
			circleBool = true;
			_circleTimer = TIMEMANAGER->getWorldTime();
		}
	}
}

// ½Ã°è¹æÇâ È¸Àü
void mobBox::circle()
{
	mobstruct.angle -= 0.02f;
	_x += cosf(mobstruct.angle)*Speed;
	_y += -sinf(mobstruct.angle)*Speed;
}

void mobBox::moving()
{
	_image = IMAGEMANAGER->findImage("Áö·Ú");
	_objNumberY = 0;
	_mobWorldTimer = TIMEMANAGER->getWorldTime();

	if (_mobWorldTimer - _mobTimer > 0.5f)
	{
		_objNumberX = mobCount;
		mobCount++;
		_mobTimer = TIMEMANAGER->getWorldTime();
		if (mobCount == 4)
		{
			mobCount = 0;
		}
	}
}

void mobBox::bulletEffect()
{
	_bulletRc = RectMakeCenter(_rcTemp.left, _rcTemp.top, 100, 100);

	_effectImage = IMAGEMANAGER->findImage("ÃÑ¾ËÆø¹ß");

	_effectNumberY = 0;

	_boomWorldTimer = TIMEMANAGER->getWorldTime();

	if (_boomWorldTimer - _boomTimer > 0.05f)
	{
		_effectNumberX = count;
		count++;
		_boomTimer = TIMEMANAGER->getWorldTime();
		if (count == 6)
		{
			count = 0;
			_effectBullet = false;
		}
	}
}

//»óÇÏÀÌµ¿
void mobBox::moving2()
{
	_updownWorldTimer = TIMEMANAGER->getWorldTime();
	if (updownBool)
	{
		if (_updownWorldTimer - _updownTimer < 2.0f)
		{
			_y--;
		}
		else
		{
			updownBool = false;
			_updownTimer = TIMEMANAGER->getWorldTime();
		}
	}
	if (!updownBool)
	{
		if (_updownWorldTimer - _updownTimer < 2.0f)
		{
			_y++;
		}
		else
		{
			updownBool = true;
			_updownTimer = TIMEMANAGER->getWorldTime();
		}
	}
}