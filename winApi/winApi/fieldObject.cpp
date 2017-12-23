#include "stdafx.h"
#include "fieldObject.h"

//박스 이미지
HRESULT fieldObject::init(string imageName,OBJECTDISCERN discernNum, int appearMapNum, POINT pos)
{
	_image = IMAGEMANAGER->findImage(imageName);
	_discernNum = discernNum;
	_appearMapNum = appearMapNum;

	_x = pos.x;
	_y = pos.y;
	_playerPoint.x = 200;
	_playerPoint.y = 500;

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

void fieldObject::boomEffect()
{
}
