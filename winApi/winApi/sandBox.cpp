#include "stdafx.h"
#include "sandBox.h"

HRESULT sandBox::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{

	// 플레이어 상호작용 스타모양 박스
	_appearMapNum = 0;
	_discernNum = sandbox;
	_x = 500.0f;
	_y = 300.0f;
	_rc = RectMakeCenter(_x, _y, 100, 100);

	fieldObject::init(objectName, discernNum, mapNum, pos);

	_image = IMAGEMANAGER->findImage("박스오브젝트");

	//오브젝트 상자 번호
	_objNumberX = 0;
	_objNumberY = 1;
	_boomTimer = TIMEMANAGER->getWorldTime();
	_boomWorldTimer = TIMEMANAGER->getWorldTime();
	count = 0;


	return S_OK;
}

void sandBox::update(void)
{
	move();
	if (_state == 3)
	{
		boomEffect();
	}
}

void sandBox::move()
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

void sandBox::boomEffect()
{
	_image = IMAGEMANAGER->findImage("폭발이미지");
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
