#include "stdafx.h"
#include "fieldBoomMid.h"


HRESULT fieldBoomMid::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{
	// ÆøÅº »óÈ£ÀÛ¿ë ¹Ú½º
	_appearMapNum = 0;
	_discernNum = sandbox;
	_x = 500.0f;
	_y = 300.0f;
	_rc = RectMakeCenter(_x, _y, 100, 100);

	fieldObject::init(objectName, discernNum, mapNum, pos);

	_image = IMAGEMANAGER->findImage("¸ÊÆø¹ß");

	//¿ÀºêÁ§Æ® »óÀÚ ¹øÈ£
	_objNumberX = 1;
	_objNumberY = 1;
	_boomTimer = TIMEMANAGER->getWorldTime();
	_boomWorldTimer = TIMEMANAGER->getWorldTime();
	count = 0;
	bullectCount = 0;

	return S_OK;
}

void fieldBoomMid::update(POINT playerPosition, vector<bullet*> bulletPos)
{
	move();
	for (int i = 0; i < bulletPos.size(); i++)
	{
		if (IntersectRect(&_rcTemp, &bulletPos[i]->getrc(), &_rc))
		{
			bulletPos[i]->setState(2);
			_effectBullet = true;
		}
	}
	if (_effectBullet)
	{
		bulletEffect();
	}
	if (_state == 3)
	{
		boomEffect();
	}
}

void fieldBoomMid::move()
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

void fieldBoomMid::boomEffect()
{
	_image = IMAGEMANAGER->findImage("Æø¹ßÀÌ¹ÌÁö");
	_objNumberY = 0;
	_boomWorldTimer = TIMEMANAGER->getWorldTime();

	if (_boomWorldTimer - _boomTimer > 0.08f)
	{
		_objNumberX = count;
		count++;
		_boomTimer = TIMEMANAGER->getWorldTime();
		if (count == 5)
		{
			count = 0;
			_state = 2;
		}
	}
}

void fieldBoomMid::bulletEffect()
{
	_bulletRc = RectMakeCenter(_rcTemp.left, _rcTemp.top, 100, 100);

	_effectImage = IMAGEMANAGER->findImage("ÃÑ¾ËÆø¹ß");

	_effectNumberY = 0;

	_bullectWorldTimer = TIMEMANAGER->getWorldTime();

	if (_bullectWorldTimer - _bullectTimer > 0.05f)
	{
		_effectNumberX = bullectCount;
		bullectCount++;
		_bullectTimer = TIMEMANAGER->getWorldTime();

		if (bullectCount == 6)
		{
			bullectCount = 0;
			_effectBullet = false;
		}
	}
}