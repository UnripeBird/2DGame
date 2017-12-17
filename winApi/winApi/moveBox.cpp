#include "stdafx.h"
#include "moveBox.h"

HRESULT moveBox::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{
	fieldObject::init(objectName, discernNum, mapNum, pos);
	return S_OK;
}

void moveBox::update(void)
{
	move();
}

void moveBox::move()
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
