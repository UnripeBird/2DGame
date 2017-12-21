#include "stdafx.h"
#include "fieldObject.h"

HRESULT fieldObject::init(void)
{
	// 플레이어 상호작용 스타모양 박스
	_appearMapNum = 0;
	_discernNum = starbox;
	_x = 300.0f;
	_y = 300.0f;
	_rc = RectMakeCenter(_x, _y, 100, 100);

	// 플레이어 상호작용 스톤박스


	return S_OK;
}

HRESULT fieldObject::init(string imageName,OBJECTDISCERN discernNum, int appearMapNum, POINT pos)
{
	_image = IMAGEMANAGER->findImage(imageName);

	_discernNum = discernNum;
	_appearMapNum = appearMapNum;

	_x = pos.x;
	_y = pos.y;

	if (_image == NULL)
	{
		_rc = RectMakeCenter(_x, _y, 100, 100);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}

	return S_OK;
}

void fieldObject::release(void)
{
}

void fieldObject::update(void)
{
}
