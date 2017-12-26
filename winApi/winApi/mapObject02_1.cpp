#include "stdafx.h"
#include "mapObject02_1.h"

HRESULT mapObject02_1::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{
	// ÆøÅº »óÈ£ÀÛ¿ë ¹Ú½º
	_appearMapNum = 0;
	_discernNum = ironbox;
	_x = 500.0f;
	_y = 300.0f;
	_rc = RectMakeCenter(_x, _y, 100, 100);

	fieldObject::init(objectName, discernNum, mapNum, pos);

	_image = IMAGEMANAGER->findImage("¸Ê02¿ÀºêÁ§Æ®1");

	//¿ÀºêÁ§Æ® »óÀÚ ¹øÈ£
	_objNumberX = 0;
	_objNumberY = 0;
	_boomTimer = TIMEMANAGER->getWorldTime();
	_boomWorldTimer = TIMEMANAGER->getWorldTime();
	count = 0;
	bullectCount = 0;

	return S_OK;
}

void mapObject02_1::update(POINT playerPosition, vector<bullet*> bulletPos)
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
}

void mapObject02_1::move()
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

void mapObject02_1::bulletEffect()
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

