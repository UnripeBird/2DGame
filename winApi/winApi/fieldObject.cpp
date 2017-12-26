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

	_effectBullet = false;

	//임시 플레이어 좌표 - 플레이어에서 받아와야함 - 받아와야할 값 - 플레이어cpp 에서의 getPos
	_playerPoint.x = 100;
	_playerPoint.y = 500;
	//임시 플레이어 방향 - 플레이어에서 받아와야함 - 받아와야할 값 - 플레이어cpp 에서의 _curRight
	_curRight = true;
	_numK = 0;
	if (_image == NULL)
	{
		_rc = RectMakeCenter(_x, _y, 100, 100);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}

	_effectImage = IMAGEMANAGER->findImage("총알폭발");
	_discernNum = discernNum;
	_appearMapNum = appearMapNum;

	_x = pos.x;
	_y = pos.y;

	//임시 플레이어 좌표 - 플레이어에서 받아와야함 - 받아와야할 값 - 플레이어cpp 에서의 getPos
	_playerPoint.x = 100;
	_playerPoint.y = 500;
	//임시 플레이어 방향 - 플레이어에서 받아와야함 - 받아와야할 값 - 플레이어cpp 에서의 _curRight
	_curRight = true;

	if (_effectImage == NULL)
	{
		_rc = RectMakeCenter(_x, _y, 100, 100);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _effectImage->getFrameWidth(), _effectImage->getFrameHeight());
	}

	return S_OK;
}


void fieldObject::release(void)
{
}

void fieldObject::update(POINT playerPosition, vector<bullet*> bulletPos)
{
}

void fieldObject::boomEffect()
{
}

void fieldObject::absorption(POINT playerPos)
{

}
