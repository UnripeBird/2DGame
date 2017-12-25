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
	_image = IMAGEMANAGER->findImage("박스오브젝트");

	_objNumberX = 0;
	_objNumberY = 2;

	ironrand = 0;

	return S_OK;
}

void ironBox::update(POINT playerPosition, vector<bullet*> bulletPos)
{

	move();
	for (int i = 0; i < bulletPos.size(); i++)
	{
		if (IntersectRect(&_rcTemp, &bulletPos[i]->getrc(), &_rc))
		{
			bulletPos[i]->setState(2);
		}
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

