#include "stdafx.h"
#include "StarBox.h"
#include "player.h"

HRESULT StarBox::init(string objectName, OBJECTDISCERN discernNum, int mapNum, POINT pos)
{
	
	// �÷��̾� ��ȣ�ۿ� ��Ÿ��� �ڽ�
	_appearMapNum = 0;
	_discernNum = starbox;
	_x = 500.0f;
	_y = 300.0f;
	_rc = RectMakeCenter(_x, _y, 100, 100);

	fieldObject::init(objectName, discernNum, mapNum, pos);

	_image = IMAGEMANAGER->findImage("�ڽ�������Ʈ");

	//������Ʈ ���� ��ȣ
	_objNumberX = 0;
	_objNumberY = 4;
	_boomTimer = TIMEMANAGER->getWorldTime();
	_boomWorldTimer = TIMEMANAGER->getWorldTime();
	count = 0;


	return S_OK;
}

void StarBox::update(void)
{
	move();
	if (_state == 3)
	{
		boomEffect();
	}

	if (KEYMANAGER->isStayKeyDown('X'))
	{
		absorption();
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
}

void StarBox::boomEffect(void)
{
	_image = IMAGEMANAGER->findImage("�����̹���");
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

//�÷��̾���� ��ȣ�ۿ� �Լ�
void StarBox::absorption()
{
	if (_playerPoint.x < _x)
	{
		_x--;
		_y--;
	}
}
