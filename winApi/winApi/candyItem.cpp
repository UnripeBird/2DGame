#include "stdafx.h"
#include "candyItem.h"

HRESULT candyItem::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{
	_appearMapNum = 0;
	_discernNum = candyitem;
	_x = 500.0f;
	_y = 300.0f;
	_rc = RectMakeCenter(_x, _y, 100, 100);
	count = 0;
	fieldObject::init(objectName, discernNum, mapNum, pos);

	_image = IMAGEMANAGER->findImage("아이템");

	_objNumberX = 0;
	_objNumberY = 1;

	_boomTimer = TIMEMANAGER->getWorldTime();
	_boomWorldTimer = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void candyItem::update(POINT playerPosition, vector<bullet*> bulletPos)
{
	move();
	flash();
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		starabso(playerPosition);
	}

	for (int i = 0; i < bulletPos.size(); i++)
	{
		if (IntersectRect(&_rcTemp, &bulletPos[i]->getrc(), &_rc))
		{
			wind(playerPosition);
		}
	}
}

//플레이어 바람공격 맞았을시 아이템 밀려나기
void candyItem::wind(POINT playerPos)
{
	//플레이어 좌표로 좌우 방향 체크
	if (playerPos.x < _x)
	{
		_curRight = true;
	}
	else
	{
		_curRight = false;
	}

	if (_curRight)
	{
		_x -= 1;
	}
	else
	{
		_x += 1;
	}
}
void candyItem::move()
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

void candyItem::flash()
{
	_image = IMAGEMANAGER->findImage("아이템");
	_objNumberY = 1;
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
//플레이어흡수 상호작용 함수
void candyItem::starabso(POINT playerPos)
{
	//플레이어 좌표로 좌우 방향 체크
	if (playerPos.x < _x)
	{
		_curRight = true;
	}
	else
	{
		_curRight = false;
	}

	//방향에 따라 흡수위치 달라짐
	if (_curRight) // 오른쪽
	{
		if (playerPos.y < _y)
		{
			_y -= speed;
			_x -= speed;

			if (playerPos.x + 60 >= _x)
			{
				_state = 4;
			}
		}
		else
		{
			_y += speed;
			_x -= speed;
			if (playerPos.x + 60 >= _x)
			{
				_state = 4;
			}
		}


	}//오른쪽 흡수 끝

	else // 왼쪽 흡수
	{
		if (playerPos.y > _y)
		{
			_y += speed;
			_x += speed;
			if (playerPos.x - 60 <= _x)
			{
				_state = 4;
			}
		}
		else
		{
			_y -= speed;
			_x += speed;
			if (playerPos.x - 60 <= _x)
			{
				_state = 4;
			}
		}
	}//왼쪽 흡수 끝
}