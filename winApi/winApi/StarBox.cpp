#include "stdafx.h"
#include "StarBox.h"
#include "player.h"

HRESULT StarBox::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{
	
	// 플레이어 상호작용 스타모양 박스
	_appearMapNum = 0;
	_discernNum = starbox;
	_x = 500.0f;
	_y = 300.0f;
	_rc = RectMakeCenter(_x, _y, 100, 100);

	fieldObject::init(objectName, discernNum, mapNum, pos);

	_image = IMAGEMANAGER->findImage("박스오브젝트");
	_mapState = mapNum;
	//오브젝트 상자 번호
	_objNumberX = 0;
	_objNumberY = 4;
	_boomTimer = TIMEMANAGER->getWorldTime();
	_boomWorldTimer = TIMEMANAGER->getWorldTime();
	count = 0;
	bullectCount = 0;
	_curRight = true;
	_Loop = false;
	return S_OK;
}

void StarBox::update(POINT playerPosition, vector<bullet*> bulletPos)
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

	if (_state == 3)
	{
		boomEffect();
	}
	else if (_effectBullet)
	{
		bulletEffect();
		boomEffectBullet();
	}
}

void StarBox::move()
{
	if (_image == NULL)
	{
		_rc = RectMakeCenter(_x, _y, 100, 100);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}
	if (_mapState != 3) return;

	if (_x <= 592 && !_Loop)
	{
		_x += 1.0f;
	}
	else
	{
		_Loop = true;
	}
	if(_x>=31&&_Loop)
	{
		_x -= 1.0f;
	}
	else
	{
		_Loop = false;
	}
}

void StarBox::boomEffect(void)
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

void StarBox::boomEffectBullet(void)
{
	_image = IMAGEMANAGER->findImage("폭발이미지");
	_objNumberY = 0;
	_boomWorldTimer = TIMEMANAGER->getWorldTime();

	if (_boomWorldTimer - _boomTimer > 0.08f)
	{
		_objNumberX = count;
		count++;
		_boomTimer = TIMEMANAGER->getWorldTime();
		if (count == 4)
		{
			count = 0;
			_state = 4;
		}
	}
}

//플레이어흡수 상호작용 함수
void StarBox::absorption(POINT playerPos)
{
	_image = IMAGEMANAGER->findImage("별오브젝트");
	_objNumberX = 0;
	_objNumberY = 0;

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
			_y-=speed;
			_x-= speed;
		}
		else
		{
			_y+= speed;
			_x-= speed;
		}


	}//오른쪽 흡수 끝

	else // 왼쪽 흡수
	{
		if (playerPos.y > _y)
		{
			_y+= speed;
			_x+= speed;
		}
		else
		{
			_y-= speed;
			_x+= speed;
		}
	}//왼쪽 흡수 끝

}

void StarBox::bulletEffect()
{

	_bulletRc = RectMakeCenter(_rcTemp.left, _rcTemp.top, 100, 100);

	_effectImage = IMAGEMANAGER->findImage("총알폭발");

	_effectNumberY = 0;

	_bullectWorldTimer = TIMEMANAGER->getWorldTime();

	if (_bullectWorldTimer - _bullectTimer > 0.05f)
	{
		_effectNumberX = bullectCount;
		bullectCount++;
		_bullectTimer = TIMEMANAGER->getWorldTime();

		if (bullectCount == 6)
		{
			bullectCount = 0;
			_effectBullet = false;
		}
	}
}
