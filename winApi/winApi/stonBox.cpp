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

	//상자 흡수용 타이머
	_absoCount = 0;
	_absoTimer = TIMEMANAGER->getWorldTime();
	_absoWorldTimer = TIMEMANAGER->getWorldTime();

	//상자 좌표 초기
	box_x = _x;

	//좌우판단
	curRight = true;
	count = 0;
	return S_OK;
}

void stonBox::update(POINT playerPosition, vector<bullet*> bulletPos)
{
	move();

	for (int i = 0; i < bulletPos.size(); i++)
	{
		if (IntersectRect(&_rcTemp, &bulletPos[i]->getrc(), &_rc))
		{
			_effectBullet = true;
			bulletPos[i]->setState(2);
		}
	}
	if (_effectBullet)
	{
		bulletEffect();
	}
}

void stonBox::move()
{
	if (_image == NULL)
	{
		_rc = RectMakeCenter(_x, _y, 100, 100);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth()+5, _image->getFrameHeight());
	}
}

//플레이어 흡수에 끌리는 오브젝트 함수 만들 예정
void stonBox::absorption(POINT playerPoint)
{
	if (playerPoint.x < _x)
	{
		curRight = true;
	}
	else
	{
		curRight = false;
	}

	if (curRight) // - 플레이어 오른쪽 방향
	{
		_absoWorldTimer = TIMEMANAGER->getWorldTime();
		countR++;
		countL++;
		if (countR % 8 == 0)
		{
			_x -= 5;
		}
		if (countL % 16 == 0)
		{
			_x += 8;
		}
		

		if (_absoWorldTimer - _absoTimer > 0.01f)
		{
			box_x = _x;
			_absoTimer = TIMEMANAGER->getWorldTime();
		}
	else
	{
		_x = box_x - 1;
	}
}//현재 방향이 트루일때

	else//현재 방향이 펄스일때 - 플레이어 왼쪽 방향
	{
			_absoWorldTimer = TIMEMANAGER->getWorldTime();
			countR++;
			countL++;
			if (countR % 8 == 0)
			{
				_x += 5;
			}
			if (countL % 16 == 0)
			{
				_x -= 8;
			}


			if (_absoWorldTimer - _absoTimer > 0.01f)
			{
				box_x = _x;
				_absoTimer = TIMEMANAGER->getWorldTime();
			}
		else
		{
			_x = box_x + 1;
		}
	}
}

void stonBox::bulletEffect()
{

	_bulletRc = RectMakeCenter(_rcTemp.left, _rcTemp.top, 100, 100);

	_effectImage = IMAGEMANAGER->findImage("총알폭발");

	_effectNumberY = 0;

	_boomWorldTimer = TIMEMANAGER->getWorldTime();

	if (_boomWorldTimer - _boomTimer > 0.05f)
	{
		_effectNumberX = count;
		count++;
		_boomTimer = TIMEMANAGER->getWorldTime();
		if (count == 6)
		{
			count = 0;
			_effectBullet = false;
		}
	}
}
