#include "stdafx.h"
#include "lifeItem.h"

HRESULT lifeItem::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{
	_appearMapNum = 0;
	_discernNum = upItem;
	_x = 500.0f;
	_y = 300.0f;
	_rc = RectMakeCenter(_x, _y, 100, 100);
	count = 0;
	fieldObject::init(objectName, discernNum, mapNum, pos);

	_image = IMAGEMANAGER->findImage("아이템");

	_objNumberX = 0;
	_objNumberY = 0;

	_boomTimer = TIMEMANAGER->getWorldTime();
	_boomWorldTimer = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void lifeItem::update(void)
{
	move();
	flash();
}

void lifeItem::move()
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

void lifeItem::flash()
{
	_image = IMAGEMANAGER->findImage("아이템");
	_objNumberY = 0;
	_boomWorldTimer = TIMEMANAGER->getWorldTime();

	if (_boomWorldTimer - _boomTimer > 0.1f)
	{
		_objNumberX = count;
		count++;
		_boomTimer = TIMEMANAGER->getWorldTime();
		if (count == 6)
		{
			count = 0;
		}
		//if (count == 2)
		//{
		//	count = 0;
		//	_state = 2;
		//}
	}
}
