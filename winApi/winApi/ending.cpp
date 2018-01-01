#include "stdafx.h"
#include "ending.h"

HRESULT ending::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{
	_appearMapNum = 4;
	_discernNum = ENDING;
	_x = 100.0f;
	_y = 100.0f;
	_rc = RectMakeCenter(_x, _y, 200, 200);

	count = 0;
	bullectCount = 0;
	fieldObject::init(objectName, discernNum, mapNum, pos);

	_image = IMAGEMANAGER->findImage("log");
	_objNumberX = 0;
	_objNumberY = 0;

	_boomTimer = TIMEMANAGER->getWorldTime();
	_boomWorldTimer = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void ending::update(POINT playerPosition, vector<bullet*> bulletPos)
{
	move();
}

void ending::move()
{
	_y-=0.8f;

	if (_image == NULL)
	{
		_rc = RectMakeCenter(_x, _y, 100, 100);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}
}
