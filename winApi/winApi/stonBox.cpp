#include "stdafx.h"
#include "stonBox.h"

HRESULT stonBox::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{
	_appearMapNum = 0;
	_discernNum = stonbox;
	_x = 200.0f;
	_y = 100.0f;
	_rc = RectMakeCenter(_x, _y, 100, 100);

	fieldObject::init(objectName, discernNum, mapNum, pos);

	_image = IMAGEMANAGER->findImage("박스오브젝트");
	_objNumberX = 0;
	_objNumberY = 6;

	return S_OK;
}

void stonBox::update(void)
{
	move();
}

void stonBox::move()
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

//플레이어 흡수에 끌리는 오브젝트 함수 만들 예정
void stonBox::traipse(void)
{

}
