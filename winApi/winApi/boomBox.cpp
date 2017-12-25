#include "stdafx.h"
#include "boomBox.h"


HRESULT boomBox::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{
	_appearMapNum = 0;
	_discernNum = boombox;
	_x = 500.0f;
	_y = 300.0f;
	_rc = RectMakeCenter(_x, _y, 100, 100);
	count = 0;
	fieldObject::init(objectName, discernNum, mapNum, pos);

	_image = IMAGEMANAGER->findImage("박스오브젝트");
	_objNumberX = 0;
	_objNumberY = 0;

	_boomTimer = TIMEMANAGER->getWorldTime();
	_boomWorldTimer = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void boomBox::update(POINT playerPosition, vector<bullet*> bulletPos)
{
	move();
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_state = 3;
	}

	for (int i = 0; i < bulletPos.size(); i++)
	{
		if (IntersectRect(&_rcTemp, &bulletPos[i]->getrc(), &_rc))
		{
			_state = 3;
			bulletPos[i]->setState(2);
		}
	}

	if (_state == 3)
	{
		boomEffect();
	}

}

void boomBox::move(void)
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

void boomBox::boomEffect(void)
{	
	_image = IMAGEMANAGER->findImage("폭발이미지");
	_objNumberY = 0;
	_boomWorldTimer = TIMEMANAGER->getWorldTime();

	if (_boomWorldTimer - _boomTimer > 0.08f)
	{
		_objNumberX=count;
		count++;
		_boomTimer = TIMEMANAGER->getWorldTime();
		if (count == 5)
		{
			count = 0;
			_state = 2;
		}
	}	
}
