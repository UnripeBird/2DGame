#include "stdafx.h"
#include "ironBox.h"
#include"randomFunction.h"


HRESULT ironBox::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{
	_appearMapNum = 0;
	_discernNum = ironbox;
	_x = 500.0f;
	_y = 300.0f;
	_rc = RectMakeCenter(_x, _y, 100, 100);

	fieldObject::init(objectName, discernNum, mapNum, pos);
	_image = IMAGEMANAGER->findImage("¹Ú½º¿ÀºêÁ§Æ®");

	_objNumberX = 0;
	_objNumberY = 2;

	ironrand = 0;
	count = 0;

	return S_OK;
}

void ironBox::update(POINT playerPosition, vector<bullet*> bulletPos)
{

	move();

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

void ironBox::move()
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
void ironBox::bulletEffect()
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

